// Ex13_10.cpp
import <iostream>;
import <memory>;
import <random>;
import <functional>;
import truckload;

auto createUniformPseudoRandomNumberGenerator(double max)
{
    std::random_device seeder;
    std::default_random_engine generator{seeder()};
    std::uniform_real_distribution distribution{1.0,max};
    return std::bind(distribution,generator);
}

int main()
{
    const double limit{99.0};
    auto random=createUniformPseudoRandomNumberGenerator(limit);

    Truckload load;
    const size_t boxCount{16};

    for(size_t i{};i<boxCount;++i)
    {
        load.addBox(std::make_shared<Box>(random(),random(),random()));
    }

    std::cout<<"The boxes in the Truckload are:\n";
    std::cout<<load;

    double maxVolume{};
    size_t maxIndex{};
    size_t i{};
    while(load[i])
    {
        if(load[i]->volume()>maxVolume)
        {
            maxIndex=i;
            maxVolume=load[i]->volume();
        }

        ++i;
    }

    std::cout<<"\nThe largest box is ";
    std::cout<<*load[maxIndex]<<std::endl;

    load.removeBox(load[maxIndex]);
    std::cout<<"\nAfter deleting the largest box, the Truckload contains:\n";
    std::cout<<load;
}