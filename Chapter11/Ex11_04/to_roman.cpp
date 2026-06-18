// Implementation of the to_roman() function
// 模块实现单元（implementation unit）：`module roman;`
// 该单元实现 `to_roman(unsigned int)`，并与其他实现单元一起组成 `roman` 模块的实现部分。
module roman;

std::string to_roman(unsigned int i)
{
  if (i > 3999) return {}; // 3999, or MMMCMXCIX, is the largest standard Roman numeral
  static const std::string ms[]{ "","M","MM","MMM" };
  static const std::string cds[]{ "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM" };
  static const std::string xls[]{ "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC" };
  static const std::string ivs[]{ "","I","II","III","IV","V","VI","VII","VIII","IX" };
  return ms[i / 1000] + cds[(i % 1000) / 100] + xls[(i % 100) / 10] + ivs[i % 10];
}
