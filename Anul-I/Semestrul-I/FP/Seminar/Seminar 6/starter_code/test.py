from currency import Currency


def test_create():
    c1 = Currency()
    assert c1.get_amount() == 0.0
    assert c1.get_unit() == "EUR"

    c2 = Currency(11)
    assert c2.get_amount() == 11
    assert c2.get_unit() == "EUR"

    c3 = Currency(15, "USD")
    assert c3.get_amount() == 15
    assert c3.get_unit() == "USD"


def test_getters_and_setters():
    c = Currency(100, "EUR")
    assert c.get_amount() == 100
    assert c.get_unit() == "EUR"

    c.set_amount(50)
    assert c.get_amount() == 50

    c.set_unit("EUR")
    assert c.get_amount() == 50
    assert c.get_unit() == "EUR"

    c = Currency(10, "EUR")
    c.set_unit("USD")
    assert c.get_amount() == 11.6
    assert c.get_unit() == "USD"

    c = Currency(10, "EUR")
    try:
        c.set_unit("GBP")
        assert False
    except TypeError:
        assert True


def test_add():
    # same unit
    c1 = Currency(10, "EUR")
    c2 = Currency(5, "EUR")
    result = c1 + c2
    assert isinstance(result, Currency)
    assert result.get_unit() == "EUR"
    assert result.get_amount() == 15

    # different units
    c1 = Currency(10, "EUR")
    c2 = Currency(5, "USD")  # 5 USD = 4.3103 EUR
    result = c1 + c2
    # round so it rounds the amount to given precision
    assert round(result.get_amount(), 4) == 14.3103
    assert result.get_unit() == "EUR"

    # different units - now unit of left operand = USD
    c1 = Currency(5.8, "USD")
    c2 = Currency(10, "EUR")  # 10 EUR = 11.6 USD
    result = c1 + c2
    assert result.get_amount() == 17.4
    assert result.get_unit() == "USD"

    c1 = Currency(10, "USD")
    result = c1 + 5  # 5 EUR = 5.8 USD
    assert round(result.get_amount(), 2) == 15.8
    assert result.get_unit() == "USD"

    c1 = Currency(10, "EUR")
    result = c1 + 5  # 5 EUR = 5.8 USD
    assert round(result.get_amount(), 2) == 15
    assert result.get_unit() == "EUR"


def test_radd():
    c1 = Currency(10, "USD")
    result = 5 + c1
    assert result.get_amount() == 15.8

    c2 = Currency(10.18, "RON")
    result = 5 + c2  # 5 EUR = 25.45 LEI
    assert round(result.get_amount(), 2) == 35.63


def test_equality():
    c1 = Currency(5.09, "RON")
    c2 = Currency(1, "EUR")
    assert c1 == c2

    c3 = Currency(10, "EUR")
    c4 = Currency(10, "USD")
    assert c3 != c4


if __name__ == "__main__":
    test_create()
    test_getters_and_setters()
    test_add()
    test_radd()
    test_equality()
    print("All tests passed.")
