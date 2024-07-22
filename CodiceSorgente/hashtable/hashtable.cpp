
namespace lasd {

    template<>
    class Hashable<int>{
        public:
            unsigned long operator()(const int &dat) const noexcept
            {
                return dat*dat;
            }
    };


    template <>
    class Hashable<double>
    {
        public:
            unsigned long operator()(const double &dat) const noexcept
            {
                long intpart = floor(dat);
                long fracpart = pow(2,24) * (dat-intpart);
                return (intpart * fracpart); 
            }
    };


    template <>
    class Hashable<std::string>
    {
        public:
            unsigned long operator()(const std::string &str) const noexcept
            {
                unsigned long hash = 3581;
                for(long unsigned int i = 0;i<str.size();i++)
                {
                    hash = (hash << 5) + str[i];
                }
                return hash;
            }
    };
}
