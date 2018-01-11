from numba import jit

@jit
def print_hello_world_jit():
	"""
	Es wird eine Funktion erstellt welche ein Hello World in Ascii-Art ausgibt.

	Diese Funktion wurde mit dem sogenannten @jit decorator versehen.

	jit steht für Just In Time und bedeutet dass der Code so läuft, als ob er direkt in C geschrieben wären würde.

	Dies führt zu enormen Perfomance-Gewinn im Vergleich zu herkömmlichen Python
	:return:
	"""
	print("""  _   _   _____   _       _        ___     __        __   ___    ____    _       ____
 | | | | | ____| | |     | |      / _ \    \ \      / /  / _ \  |  _ \  | |     |  _ \
 | |_| | |  _|   | |     | |     | | | |    \ \ /\ / /  | | | | | |_) | | |     | | | |
 |  _  | | |___  | |___  | |___  | |_| |     \ V  V /   | |_| | |  _ <  | |___  | |_| |
 |_| |_| |_____| |_____| |_____|  \___/       \_/\_/     \___/  |_| \_\ |_____| |____/
                                                                                       """)
if __name__ == '__main__':
	print_hello_world_jit()