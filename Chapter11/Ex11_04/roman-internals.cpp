// Implementation of the internal from_roman() function
// 模块分区（module partition）：`module roman:internals;`
// 这是模块的内部实现细节。该分区未被 `export`，因此对模块外部不可见。
// 只有同一模块的实现单元可以 `import :internals;` 来使用这里的辅助函数。
module roman:internals;

unsigned int from_roman(char c)
{
  switch (c)
  {
  case 'I': return 1;    case 'V': return 5;   case 'X': return 10;
  case 'L': return 50;   case 'C': return 100; case 'D': return 500;
  case 'M': return 1000; default:  return 0;
  }
}
