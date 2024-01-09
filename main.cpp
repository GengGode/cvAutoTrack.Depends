// #include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>
#include <cereal/cereal.hpp>
#include <cereal/types/unordered_map.hpp>
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
namespace cereal{
template <class Archive>
inline void save(Archive &ar,const cv::Mat &mat) 
{
    int rows, cols, type;
    bool continuous;

    rows = mat.rows;
    cols = mat.cols;
    type = mat.type();
    continuous = mat.isContinuous();

    ar & rows & cols & type & continuous;

    if (continuous)
    {
        const int data_size = rows * cols * static_cast<int>(mat.elemSize());
        auto mat_data = cereal::binary_data(mat.ptr(), data_size);
        ar & mat_data;
    }
    else
    {
        const int row_size = cols * static_cast<int>(mat.elemSize());
        for (int i = 0; i < rows; i++)
        {
            auto row_data = cereal::binary_data(mat.ptr(i), row_size);
            ar & row_data;
        }
    }
};
template <class Archive>
inline void load(Archive &ar, cv::Mat &mat) 
{
    int rows, cols, type;
    bool continuous;

    ar & rows & cols & type & continuous;

    if (continuous)
    {
        mat.create(rows, cols, type);
        const int data_size = rows * cols * static_cast<int>(mat.elemSize());
        auto mat_data = cereal::binary_data(mat.ptr(), data_size);
        ar & mat_data;
    }
    else
    {
        mat.create(rows, cols, type);
        const int row_size = cols * static_cast<int>(mat.elemSize());
        for (int i = 0; i < rows; i++)
        {
            auto row_data = cereal::binary_data(mat.ptr(i), row_size);
            ar & row_data;
        }
    }
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
    cv::imwrite("test.jpg", image);
    std::ofstream os("test_img.bin", std::ios::binary);
    cereal::BinaryOutputArchive archive(os);
    archive(image);
    os.close();

    cv::Mat image2;
    std::ifstream is("test_img.bin", std::ios::binary);
    cereal::BinaryInputArchive archive2(is);
    archive2(image2);
    is.close();

    cv::imwrite("test2.jpg", image2);



    }

    return 0;
}