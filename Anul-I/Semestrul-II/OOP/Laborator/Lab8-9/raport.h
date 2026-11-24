#pragma once
#include <map>
#include <string>

class RaportDTO {
private:
	std::map<std::string, int> raport;
public:
	RaportDTO() noexcept = default;
	void incrementare_raport(const std::string& tip);
	const std::map<std::string, int>& get_raport() const noexcept;
};