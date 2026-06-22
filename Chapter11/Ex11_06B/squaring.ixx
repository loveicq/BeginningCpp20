export module squaring;

export namespace math
{
	const double sqrt2{ 1.4142134562373095 };
	auto square(const auto& x) { return x * x; }
	auto pow4(const auto& x) { return square(square(x)); }
}