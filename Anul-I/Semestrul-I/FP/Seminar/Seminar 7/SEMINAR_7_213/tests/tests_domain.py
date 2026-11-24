from domain.entities import Melodie
from domain.validator import ValidatorMelodie


# TO DO: test creare Melodie, getters, setters
def test_melodie():
    pass


def test_validation():
    m = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 2.44)
    val = ValidatorMelodie()
    val.validate(m)

    #melodie invalida - gen invalid
    m1 = Melodie(1324, "Perfect Strangers", "Deep Purple", "alt gen", 2.44)
    try:
        val.validate(m1)
        assert False
    except ValueError:
        assert True

    #melodie invalida - durata invalida
    m1 = Melodie(1324, "Perfect Strangers", "Deep Purple", "rock", 23.97)
    try:
        val.validate(m1)
        assert False
    except ValueError:
        assert True


if __name__ == "__main__":
    test_melodie()
    test_validation()
