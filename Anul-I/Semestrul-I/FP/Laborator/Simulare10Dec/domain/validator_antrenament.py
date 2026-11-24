class ValidationError(Exception):
    pass

class ValidatorAntrenament:
    def validate(self, antrenament) -> None:
        """
        Valideaza toate atributele unui antrenament
        :param antrenament: antrenamentul validat
        :raises ValidationError: daca valoare unei atribute nu este valida
        """
        errors = []
        if not isinstance(antrenament.get_cod(), int) or antrenament.get_cod() <= 0:
            errors.append("Codul trebuie sa fie un numar natural nenul!")
        if not isinstance(antrenament.get_pret(), int) or antrenament.get_pret() <= 0:
            errors.append("Pretul trebuie sa fie un numar natural nenul!")
        if not isinstance(antrenament.get_descriere(), str) or len(antrenament.get_descriere()) == 0 or antrenament.get_descriere().find(',') != -1:
            errors.append("Descrierea trebuie sa fie un sir de caractere nevid si fara virgule!")
        if not isinstance(antrenament.get_tip(), str) or len(antrenament.get_tip()) == 0:
            errors.append("Tipul trebuie sa fie un sir de caractere nevid!")
        if len(errors) > 0:
            raise ValidationError('\n'.join(errors))