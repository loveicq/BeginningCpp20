//roman.ixx
export module roman;
import <string>;
import <string_view>;

export std::string to_roman(unsigned int i);
export unsigned int from_roman(std::string_view roman);
