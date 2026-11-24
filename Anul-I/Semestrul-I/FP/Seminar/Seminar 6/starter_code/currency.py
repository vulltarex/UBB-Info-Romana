# we define a new type - name of new type: Currency
# characterized by amount, currency unit
class Currency:
    # class attribute - shared by all instances
    exchange_rates = {'EUR': 1.0, 'USD': 1.16, 'RON': 5.09}

    def __init__(self, amount=0.0, unit="EUR"):
        # called when a new object is created
        # amount, unit: instance attributes
        # print("Init called")
        self.__amount = amount
        self.__unit = unit

    def get_amount(self):
        return self.__amount

    def get_unit(self):
        return self.__unit

    def set_amount(self, new_amount):
        self.__amount = new_amount

    def set_unit(self, new_unit):
        """
        Set a new currency unit
        :param new_unit: the new currency unit, new_unit one of RON, EUR, USD
        :return: -; amount set at value obtained in new_unit, unit = new_unit
        :raises: TypeError if new_unit not one of the types allowed
        """
        if new_unit not in ['RON', 'EUR', 'USD']:
            raise TypeError("Currency unit not allowed.")
        self.__amount = self.__convert_between_units(self.__amount, self.__unit, new_unit)
        self.__unit = new_unit

    def __add__(self, other):
        # print("Add called")
        if isinstance(other, Currency):
            other_converted = self.__convert_between_units(other.__amount, other.__unit, self.__unit)
        elif isinstance(other, (int, float)):
            other_converted = self.__convert_between_units(other, "EUR", self.__unit)
        else:
            return NotImplemented
        return Currency(other_converted + self.__amount, self.__unit)

    # by default, == would compare identity
    def __eq__(self, other):
        if not isinstance(other, Currency):
            return NotImplemented
        amount_other_in_self_unit = self.__convert_between_units(other.__amount, other.__unit, self.__unit)
        return self.__amount == amount_other_in_self_unit

    def __radd__(self, other):
        return self.__add__(other)

    def __str__(self):
        return f"Money: {self.__amount} {self.__unit}"

    """
    Static methods: generally, used for utility functions
    that don't need to modify or access class or instance data,
    but what they do still logically belongs within the class’s namespace
    """

    @staticmethod
    def __convert_between_units(amount, from_unit, to_unit):
        return amount / Currency.exchange_rates[from_unit] * Currency.exchange_rates[to_unit]

    """
    Class methods: can be used for alternative constructors
    """

    @classmethod
    def from_string(cls, currency_str):
        """
        Creates a Currency object from a string
        :param currency_str: string sub forma 20 RON
        :return: obiect Currency cu valorile setate
        """
        parts = currency_str.split()
        return cls(float(parts[0]), parts[1])
