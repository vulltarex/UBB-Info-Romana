import unittest


def run_all():
    loader = unittest.TestLoader()
    suite = loader.discover('.', pattern='test_*.py')

    runner = unittest.TextTestRunner()
    runner.run(suite)


if __name__ == '__main__':
    run_all()
    print("Toate testele au trecut!")