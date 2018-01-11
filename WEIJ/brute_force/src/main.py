from pprint import pprint
try:
    import md5
    digest = lambda text: md5.new(text).hexdigest()
except ImportError:
    import hashlib
    digest = lambda text: hashlib.md5(text.encode()).hexdigest()

passwords = {}
with open("passwort.txt") as file:
    for word in (line.strip() for line in file):
        passwords.setdefault(digest(word), []).append(word)

pprint(passwords)