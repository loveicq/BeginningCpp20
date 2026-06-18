// Interface file for a Roman numerals module
// 模块接口单元（module interface unit）
// 定义并导出模块 `roman` 的对外 API。
// 外部用户通过 `import roman;` 可以使用下列被导出的函数。
export module roman;
import <string>;
import <string_view>;

export std::string to_roman(unsigned int i);
export unsigned int from_roman(std::string_view roman);
