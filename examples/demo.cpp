#include <iostream>
#include <filesystem>
#include <cmath>
#include <chrono>
#include <thread>

#include "../include/ppmstream/stream/PPMStream.hpp"
#include "../include/ppmstream/stream/PPMDrawer.hpp"
#include "../include/ppmstream/math/Vec.hpp"
#include "../include/ppmstream/math/Mat.hpp"

void test1();

void test2();

void multi_thread_test2();

void test3();

void test2_simple_pattern();

void test4();

const std::filesystem::path outputs_dir("../outputs");
const std::filesystem::path output_frames_dir = outputs_dir / "output-frames";
const std::filesystem::path output_video_dir = outputs_dir / "output-video";

int main()
{
    // multi_thread_test2();
    test1();
    // test2();

    // test4();

    return 0;
}

void test1()
{
    using namespace ppmstream;

    const size_t scale = 120;
    const size_t w = 16;
    const size_t h = 9;
    const int colors = 255;
    std::string output_file_name = "black-red-chess-board.ppm";
    std::filesystem::path output_file = output_frames_dir / output_file_name;
    PPMStream ppms(output_file.c_str(), scale, w, h, colors);

    for(int y = 0; y < scale * h; ++y)
    {
        for(int x = 0; x < scale * w; ++x)
        {
            if((y/scale + x/scale) % 2)
            {
                ppms.buffer()(x, y) = {0xFF, 0x00, 0x00};
            }
            else
            {
                ppms.buffer()(x, y) = {0x00, 0x00, 0x00};
            }
        }
    }

    ppms.close();

    std::cout << "Generate " << output_file << std::endl;
}

void test2()
{
    using namespace ppmstream;

    char buff[255];
    const size_t fps = 30;
    const size_t sec = 10;
    const size_t total_frame = fps * sec;

    const int scale = 120;
    const int w = 16;
    const int h = 9;
    const int width = w * scale;
    const int height = h * scale;
    const int colors = 255;

    size_t shade_duration = 0ULL;

    std::string file_format("output-%03d.ppm");
    std::filesystem::path ppm_path_format = output_frames_dir / file_format;

    PPMStream ppms;

    for(size_t frame = 0; frame < total_frame; ++frame)
    {
        std::snprintf(buff, sizeof(buff), ppm_path_format.c_str(), frame);
        std::string output_path(buff);

        ppms.open(output_path, scale, w, h, colors, RGB::black(), OpenMode::Write);
        PPMDrawer drawer(ppms.buffer());

        float t = (float)frame / fps;
        vec2 r = {(float)width, (float)height};

        vec4 o;
        vec2 FC, p, l, i, v;

        // draw begin
        auto draw_begin = std::chrono::system_clock::now();

        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {
                o = {0.0f, 0.0f, 0.0f, 0.0f};
                FC = {(float)x, (float)y};
                p = (FC * 2.0 - r) / r.y();
                l += 4.0 - 4.0 * std::abs(0.7 - dot(p,p));
                i = {0.0f, 0.0f};
                v = p * l;

                for(; i.y()++ < 8.0; o += ( sin( v.xyyx() ) + 1.0 ) * std::abs(v.x() - v.y()))
                {
                    v += cos(v.yx() * i.y() + i + t) / i.y() + 0.7f;
                }
                o = tanh(5.0f * exp(l.x() - 4.0f - p.y() * vec4(-1,1,2,0)) / o);

                RGB::rgb_type r = o.x() * 0xFF;
                RGB::rgb_type g = o.y() * 0xFF;
                RGB::rgb_type b = o.z() * 0xFF;

                drawer.draw_point({x, y}, {r, g, b});
            }
        }

        // draw end
        auto draw_end = std::chrono::system_clock::now();

        // total draw time
        auto draw_time = std::chrono::duration_cast<std::chrono::milliseconds>(draw_end - draw_begin);

        shade_duration += draw_time.count();

        ppms.close();

        std::cout << "Generate " << output_path << "\t\t" << std::chrono::milliseconds(draw_time).count() << "ms" << std::endl;
    }

    std::cout << "\nFINISHED\n";
    std::cout << "total shading time:\t" << static_cast<float>(shade_duration) / 1000.0f / 60.0f << "min\n";
    std::cout << "average shading time:\t" << shade_duration / total_frame << "ms\n";
    std::cout << std::endl;

    int statue = system((std::string("ffmpeg -i ") + ppm_path_format.c_str() + " -r " + std::to_string(fps) + " " + (output_video_dir / "output.mp4").c_str()).data());
}

void multi_thread_shader_of_test2(size_t fps, size_t start_frame, size_t end_frame, const std::string& ppm_path_format)
{
    using namespace ppmstream;

    char buff[255];

    const int scale = 120;
    const int w = 16;
    const int h = 9;
    const int width = w * scale;
    const int height = h * scale;
    const int colors = 255;

    PPMStream ppms;
    
    // scale of the picture
    vec2 r = {(float)width, (float)height};
    // the seconds
    float t = 0.0f;

    // the calculating elem
    vec4 o;
    vec2 FC, p, l, i, v;
    const vec4 ConstVec4(-1,1,2,0);

    RGB::rgb_type r_c;   // red channel
    RGB::rgb_type g_c;   // green channel
    RGB::rgb_type b_c;   // blue channel

    // the frame of this thread
    for(size_t frame = start_frame; frame < end_frame; ++frame)
    {
        std::snprintf(buff, sizeof(buff), ppm_path_format.data(), frame);
        std::string output_path(buff);

        // open ppm file
        ppms.open(output_path, scale, w, h, colors, RGB::black(), OpenMode::Write);
        // drawer
        PPMDrawer drawer(ppms.buffer());

        // the seconds
        t = (float)frame / fps;

        // shade start
        auto shade_start = std::chrono::system_clock::now();

        // shading algorithm
        for(int y = 0; y < height; ++y)
        {
            for(int x = 0; x < width; ++x)
            {
                o = vec4{};
                FC = {(float)x, (float)y};
                p = (FC * 2.0 - r) / r.y();
                l = vec2(4.0 - 4.0 * std::abs(0.7 - dot(p,p)));
                v = p * l;
                
                i = vec2{};
                for(; i.y()++ < 8.0; o += ( sin( v.xyyx() ) + 1.0 ) * std::abs(v.x() - v.y()))
                {
                    v += cos(v.yx() * i.y() + i + t) / i.y() + 0.7f;
                }
                o = tanh(5.0f * exp(l.x() - 4.0f - p.y() * ConstVec4) / o);

                r_c = o.x() * 0xFF;
                g_c = o.y() * 0xFF;
                b_c = o.z() * 0xFF;

                drawer.draw_point({x, y}, {r_c, g_c, b_c});
            }
        }   // shading algorithm

        // shade end
        auto shade_end = std::chrono::system_clock::now();

        // shading duration
        std::chrono::duration shading_duration = std::chrono::duration_cast<std::chrono::milliseconds>(shade_end - shade_start);

        ppms.close();

        std::cout << "Generate " << output_path << "\t\t" << shading_duration.count() << "ms" << std::endl;

    }   // frames shading

    return;
}

void multi_thread_test2()
{
    using namespace ppmstream;

    const size_t fps = 30;                  // frame per second
    const size_t sec = 10;                  // seconds
    const size_t total_frame = fps * sec;   // total frames

    // storage path
    std::string ppm_frames_format = "output-%03d.ppm";
    std::string ppm_video_format = "output.mp4";
    std::filesystem::path ppm_path_format = output_frames_dir / ppm_frames_format;
    std::filesystem::path mp4_path_format = output_video_dir / ppm_video_format;

    size_t Nthrd = 6;   // N threads
    const size_t piece = total_frame / Nthrd;  // every piece of thread

    // thread list
    std::vector<std::thread> thrds;

    // task start
    auto task_start = std::chrono::system_clock::now();

    for(size_t i = 0; i < Nthrd; ++i)
    {
        thrds.emplace_back(
            multi_thread_shader_of_test2,
            fps,
            i * piece, std::min((i + 1) * piece, total_frame),
            ppm_path_format
        );
    }

    for(size_t i = 0; i < Nthrd; ++i)
    {
        thrds[i].join();
    }

    // task end
    auto task_end = std::chrono::system_clock::now();

    // total task duration
    std::chrono::duration total_duration = std::chrono::duration_cast<std::chrono::milliseconds>(task_end - task_start);

    std::cout << "\nFINISHED\n";
    std::cout << "total shading time:\t" << static_cast<float>(total_duration.count()) / 1000.0f / 60.0f << "min\n";
    std::cout << "average shading time:\t" << total_duration.count() / total_frame << "ms\n";
    std::cout << std::endl;

    // use the ffmpeg to create the mp4
    int statue = system((std::string("ffmpeg -i ") + ppm_path_format.c_str() + " -r " + std::to_string(fps).append(" ") + mp4_path_format.c_str()).data());
}

void test3()
{
    using namespace ppmstream;

    std::string ppm_file_name = "test3-pic.ppm";
    std::filesystem::path ppm_output_path = output_frames_dir / ppm_file_name;
    const int scale = 120;
    const int width = 16 * scale;
    const int height = 9 * scale;
    const int colors = 255;

    PPMStream ppms(ppm_file_name.c_str(), width, height, colors);

    for(size_t y = 0; y < height; ++y)
    {
        for(size_t x = 0; x < width; ++x)
        {
            ppms.buffer()(x, y) = {0xAA, 0x00, 0x00};
        }
    }

    ppms.close();

    std::cout << "Generate " << ppm_output_path << std::endl;

}

void test2_simple_pattern()
{
    using namespace ppmstream;
    
    std::string output_file_name = "test2-simple-pattern.ppm";
    std::filesystem::path ppm_output_path = output_frames_dir / output_file_name;
    const int width = 800;
    const int height = 600;
    const int colors = 255;
    
    PPMStream ppms(ppm_output_path.c_str(), width, height, colors);
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            // 创建彩虹渐变
            float fx = static_cast<float>(x) / width;
            float fy = static_cast<float>(y) / height;
            
            // HSV 到 RGB 的简单转换
            float hue = fx * 360.0f;
            float saturation = 1.0f;
            float value = 1.0f - fy * 0.5f;  // 从上到下变暗
            
            int hi = static_cast<int>(hue / 60.0f) % 6;
            float f = hue / 60.0f - hi;
            float p = value * (1 - saturation);
            float q = value * (1 - f * saturation);
            float t = value * (1 - (1 - f) * saturation);
            
            float r, g, b;
            switch(hi) {
                case 0: r = value; g = t; b = p; break;
                case 1: r = q; g = value; b = p; break;
                case 2: r = p; g = value; b = t; break;
                case 3: r = p; g = q; b = value; break;
                case 4: r = t; g = p; b = value; break;
                default: r = value; g = p; b = q; break;
            }
            
            ppms.buffer()(x, y) = {
                static_cast<uint8_t>(r * 255),
                static_cast<uint8_t>(g * 255),
                static_cast<uint8_t>(b * 255)
            };
        }
    }
    
    ppms.close();
    std::cout << "Generated: " << ppm_output_path << std::endl;
}

void test4()
{
    using namespace ppmstream;

    std::string ppm_file_name = "drawer-test.ppm";
    std::filesystem::path ppm_output_path = output_frames_dir / ppm_file_name;
    const int scale = 60;
    const int w = 16;
    const int h = 9;
    const int width = w * scale;
    const int height = h * scale;
    const int colors = 255;

    PPMStream stream(ppm_output_path.c_str(), width, height, colors, RGB(0xAA, 0x00, 0x00));

    PPMDrawer drawer(stream.buffer());

// ================================================================

    const int N = 100;
    for(int i = 0; i < N; ++i)
    {
        drawer.draw_line({3 * N, i + N * 2}, {4 * N, i + N * 2 + N / 2}, RGB::black());
    }

    stream.close();
    std::cout << "Generate: " << ppm_output_path << std::endl;

}

