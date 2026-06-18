// Module implementation partitions
// 模块使用者（module consumer）示例：
// 通过 `import roman;` 使用模块导出的 API（`to_roman`、`from_roman`）。
import <iostream>;
import <string>;
import roman;

int main()
{
  std::cout << "1234 in Roman numerals is " << to_roman(1234) << std::endl;
  std::cout << "MMXX in Arabic numerals is " << from_roman("MMXX") << std::endl;
  std::cin.get();
}
