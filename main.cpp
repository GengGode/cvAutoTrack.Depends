// #include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

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
    /*
    template <class Archive>
    inline void save(Archive &ar, const cv::Mat &mat)
    {
        std::vector<uchar> buf;
        cv::imencode(".png", mat, buf);
        ar & buf;
    };
    template <class Archive>
    inline void save(Archive &ar, const std::vector<uchar> &buf)
    {
        int size = buf.size();
        ar & size;
        for (auto &i : buf)
        {
            ar & i;
        }
    };
    */

    template <class Archive>
    inline void load(Archive &ar, std::vector<uchar> &buf)
    {
        int size = 0;
        ar & size;
        buf.resize(size);
        for (int i = 0; i < size; i++)
        {
            ar &buf[i];
        }
    };

    template <class Archive>
    inline void save(Archive &ar, const cv::Mat &mat)
    {
        std::vector<uchar> buf;
        cv::imencode(".png", mat, buf);
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
        cv::Mat image = cv::Mat(100, 100, CV_8UC3, cv::Scalar(0, 0, 255));
        cv::imwrite("test.bmp", image);
        std::ofstream os("test_img.bin", std::ios::binary);
        cereal::BinaryOutputArchive archive(os);
        archive(image);
        os.close();

        cv::Mat image2;
        std::ifstream is("test_img.bin", std::ios::binary);
        cereal::BinaryInputArchive archive2(is);
        archive2(image2);
        is.close();

        cv::imwrite("test2.bmp", image2);
    }

    return 0;
}