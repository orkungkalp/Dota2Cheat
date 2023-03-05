#pragma once
template<typename T, typename Z>
inline bool StringsMatch(T a, Z b) {
	return !strcmp((const char*)a, (const char*)b);
}

template <typename I>
std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
	static const char* digits = "0123456789ABCDEF";
	std::string rc(hex_len, '0');
	for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
		rc[i] = digits[((u64)w >> j) & 0x0f];
	return rc;
}

inline bool TestStringFilters(const char* str, const std::vector<const char*>& filters) {
	for (auto& filter : filters)
		if (strstr(str, filter))
			return true;

	return false;
}

inline bool TestStringFilters(std::string_view str, const std::vector<const char*>& filters) {
	for (auto& filter : filters)
		if (str.find(filter, 0) != -1)
			return true;

	return false;
}

