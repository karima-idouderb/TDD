import funcs
import unittest

class TestFuncs(unittest.TestCase):
    def test_trois_grde_val(self):
        self.assertEqual(funcs.trois_grde_val([1, 2, 3, 4, 5]), [3,4,5])

if __name__ == '__main__':
    unittest.main()