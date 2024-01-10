// #include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#ifdef COMPRESS
// need PUBLIC zlib library
#include <zlib.h>
#endif

#include <fstream>
#include <unordered_map>
struct data
{
    int x = 0;
    int y = 0;
    int z = 0;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(x, y, z);
    }
};

class info
{
    std::unordered_map<std::string, data> data_map;

public:
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(data_map);
    }

    void add_data(std::string name, data d)
    {
        data_map[name] = d;
    }

    data get_data(std::string name)
    {
        return data_map[name];
    }
};
namespace cereal
{
    template <class Archive>
    inline void save(Archive &ar, const std::vector<uchar> &buf)
    {
#ifdef COMPRESS
        std::vector<uchar> zbuf;
        zbuf.resize(compressBound(buf.size()));
        uLongf destLen = zbuf.size();
        compress(&zbuf[0], &destLen, &buf[0], buf.size());
        zbuf.resize(destLen);

        unsigned long orig_size = buf.size();
        ar & orig_size;
#else
        auto &zbuf = buf;
#endif
        int size = zbuf.size();
        ar & size;
        for (auto &i : zbuf)
        {
            ar & i;
        }

#ifdef COMPRESS
        std::cout << "orig_size: " << orig_size << std::endl;
        std::cout << "size: " << size << std::endl;
        std::cout << "compress rate: " << (float)size / orig_size << std::endl;
#endif
    };

    template <class Archive>
    inline void load(Archive &ar, std::vector<uchar> &buf)
    {
#ifdef COMPRESS
        unsigned long orig_size = 0;
        ar & orig_size;
#endif
        int size = 0;
        ar & size;
        buf.resize(size);
        for (int i = 0; i < size; i++)
        {
            ar &buf[i];
        }

#ifdef COMPRESS
        std::vector<uchar> unzbuf;
        unzbuf.resize(orig_size);
        uncompress(&unzbuf[0], &orig_size, &buf[0], size);
        buf = unzbuf;
#endif
    };

    template <class Archive>
    inline void save(Archive &ar, const cv::Mat &mat)
    {
        std::vector<uchar> buf;
        cv::imencode(".tiff", mat, buf);
        ar & buf;
    };
    template <class Archive>
    inline void load(Archive &ar, cv::Mat &mat)
    {
        std::vector<unsigned char> buf;
        ar & buf;
        mat = cv::imdecode(buf, cv::IMREAD_UNCHANGED);
    };
} // namespace cereal
int main()
{
    // cv::Mat img = cv::imread("lena.jpg");

    spdlog::info("Welcome to {}", "cvAutoTrack.Depends");

#if 0
    {
        info i;
        i.add_data("test", data{1, 2, 3});
        i.add_data("test2", data{4, 5, 6});

        std::ofstream os("test.bin", std::ios::binary);
        cereal::BinaryOutputArchive archive(os);
        archive(i);

        os.close();

        info i2;
        std::ifstream is("test.bin", std::ios::binary);
        cereal::BinaryInputArchive archive2(is);
        archive2(i2);

        spdlog::info("{}", i2.get_data("test").x);
    }
    {
        cv::Mat image = cv::Mat(10000, 128, CV_32FC1);
        randu(image, cv::Scalar(0), cv::Scalar(255));
        cv::imwrite("test.tiff", image);
        std::ofstream os("test_img.bin", std::ios::binary);
        cereal::BinaryOutputArchive archive(os);
        archive(image);
        os.close();

        cv::Mat image2;
        std::ifstream is("test_img.bin", std::ios::binary);
        cereal::BinaryInputArchive archive2(is);
        archive2(image2);
        is.close();
        std::cout << image2.channels() << std::endl;
        std::cout << image2.type() << CV_32FC1 << std::endl;
        cv::imwrite("test2.tiff", image2);
        // auto pixel = image.at<float>(0, 0);
    }
#endif
    {
        /*
            double a = new Random(1).nextDouble();
            System.out.println(a);
            long l = Double.doubleToLongBits(a);
            int key = (int) (l & 0xffffffffL);
            int value = (int) (l >> 32);
            long result = ((long) key) << 32 | (value & 0xffffffffL);
            System.out.println(Double.longBitsToDouble(result));
        */
        auto comp = [](float a) -> std::pair<uint16_t, uint16_t>
        {
            uint32_t l = *(uint32_t *)&a;
            uint16_t value = (uint16_t)(l & 0xffff);
            uint16_t key = (uint16_t)(l >> 16);
            return std::make_pair(key, value);
        };
        auto decomp = [](std::pair<uint16_t, uint16_t> p) -> float
        {
            uint32_t result = ((uint32_t)p.first) << 16 | (p.second & 0xffff);
            return *(float *)&result;
        };
        {
            float a = 0.123456789;
            auto p = comp(a);
            auto result = decomp(p);
            if (a != result)
            {
                spdlog::error("error");
                return -1;
            }
        }

        cv::Mat image = cv::Mat(1000, 64, CV_32FC1);
        try
        {
            image = cv::imread("descriptors.tiff", cv::IMREAD_UNCHANGED); // cv::Mat(1000, 64, CV_32FC1);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            randu(image, cv::Scalar(0), cv::Scalar(255));
        }

        spdlog::info("image size: {},{}", image.cols, image.rows);
        std::vector<float> vec;
        for (int i = 0; i < image.cols; i++)
        {
            for (int j = 0; j < image.rows; j++)
            {
                vec.push_back(image.at<float>(j, i));
            }
        }
        std::ofstream vec_os("vec.bin", std::ios::binary);
        cereal::BinaryOutputArchive vec_archive(vec_os);
        vec_archive(vec);
        vec_os.close();
        spdlog::info("vec size: {}", vec.size());

        std::map<uint16_t, std::vector<uint16_t>> map;
        for (auto &i : vec)
        {
            auto p = comp(i);
            auto result = decomp(p);
            map[p.first].push_back(p.second);
        }
        std::ofstream map_os("map.bin", std::ios::binary);
        cereal::BinaryOutputArchive map_archive(map_os);
        map_archive(map);
        map_os.close();

        std::map<uint16_t, int> counts;
        std::vector<std::pair<uint16_t, int>> count_vec;
        spdlog::info("map size: {}", map.size());
        for (auto &i : map)
        {
            counts[i.first] = i.second.size();
            count_vec.push_back(std::make_pair(i.first, i.second.size()));
        }

        std::sort(count_vec.begin(), count_vec.end(), [](std::pair<uint16_t, int> a, std::pair<uint16_t, int> b) -> bool
                  { return a.second > b.second; });
        for (int i = 0; i < 10; i++)
        {
            spdlog::info("key: {:x}, count: {}", count_vec[i].first, count_vec[i].second);
        }
        for (int i = 0; i < 10; i++)
        {
            spdlog::info("key: {:x}, count: {}", count_vec[count_vec.size() - 1 - i].first, count_vec[count_vec.size() - 1 - i].second);
        }

        std::ofstream os("counts.csv");
        for (auto &i : count_vec)
        {
            os << std::hex << i.first << "," << std::dec << i.second << std::endl;
        }
        os.close();

        // std::ofstream os("test_img.json");
        // cereal::JsonOutputArchive archive(os);
        // archive(counts);
    }

    return 0;
}