// #include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

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
    void save(Archive &archive)
    {
        archive(data_map);
    }

    template <class Archive>
    void load(Archive &archive)
    {

        std::unordered_map<std::string, data> _data_map;
        archive(_data_map);
        data_map = _data_map;
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

int main()
{
    // cv::Mat img = cv::imread("lena.jpg");

    spdlog::info("Welcome to {}", "cvAutoTrack.Depends");

    info i;
    i.add_data("test", data{1, 2, 3});
    i.add_data("test2", data{4, 5, 6});

    std::ofstream os("test.bin", std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(i);

    info i2;
    std::ifstream is("test.bin", std::ios::binary);
    cereal::BinaryInputArchive archive2(is);
    archive2(i2);

    spdlog::info("{}", i2.get_data("test").x);

    return 0;
}