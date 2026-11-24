#include "raport.h"

void RaportDTO::incrementare_raport(const std::string& tip) {
	raport[tip]++;
}

const std::map<std::string, int>& RaportDTO::get_raport() const noexcept {
	return raport;
}