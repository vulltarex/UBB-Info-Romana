def citeste_cuvinte(fisier):
    with open(fisier) as f:
        return f.read().split()

spam = citeste_cuvinte('keywords_spam.txt')
ham = citeste_cuvinte('keywords_ham.txt')

cuvinte_distincte = sorted(list(set(spam + ham)))

def clasifica_email(email):
    email_words = set(email.lower().split())

    p_spam = len(spam) / (len(spam) + len(ham))
    p_ham = len(ham) / (len(spam) + len(ham))

    prod_spam = p_spam
    prod_ham = p_ham

    for w in cuvinte_distincte:
        if w in email_words:
            prod_spam *= spam.count(w) / len(spam)
            prod_ham *= ham.count(w) / len(ham)
        else:
            prod_spam *= 1 - (spam.count(w) / len(spam))
            prod_ham *= 1 - (ham.count(w) / len(ham))

    if prod_spam > prod_ham:
        return 'spam', prod_spam, prod_ham
    return 'ham', prod_spam, prod_ham

email1 = "invite your friend today to click here"
email2 = "call your friend today it's urgent thank you"

print(email1)
print(clasifica_email(email1))

print(email2)
print(clasifica_email(email2))
