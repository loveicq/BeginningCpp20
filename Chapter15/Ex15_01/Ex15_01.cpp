// Ex15_01.cpp 派生类中继承函数的行为
import boxes;

int main()
{
    Box box{20.0, 30.0, 40.0};
    ToughPack hardcase{20.0, 30.0, 40.0};

    box.showVolume();
    hardcase.showVolume();

    // 以下代码显示：如果 volume() 不是 virtual 的，通过基类指针调用只会调用基类的 volume()，而非派生类的。
    // std::cout<<"hardcase volume is "<<hardcase.volume()<<std::endl;
    // Box* box_pointer{&hardcase};
    // std::cout<<"hardcase volume through a Box* pointer is "
    //           <<box_pointer->volume()<<std::endl;
}