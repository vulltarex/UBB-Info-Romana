#include "validator.h"

void Validator::validate(Tractor& t) const {
    if (t.getId() < 0) throw ValidationException("ID invalid!");
    if (t.getDenumire().empty()) throw ValidationException("Denumirea nu poate fi vida!");
    if (t.getTip().empty()) throw ValidationException("Tipul nu poate fi vid!");
    if (t.getNumarRoti() % 2 == 1 || t.getNumarRoti() < 2 || t.getNumarRoti() > 16) throw ValidationException("Numar roti invalid!");
}
