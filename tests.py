import funcs
import unittest

class TestFuncs(unittest.TestCase):
    def test_trois_grde_val(self):
        self.assertEqual(funcs.trois_grde_val([1, 2, 3, 4, 5]), [5, 4, 3])
        self.assertEqual(funcs.trois_grde_val([6, -1, 0, 9, 5]), [9, 6, 5])
        self.assertEqual(funcs.trois_grde_val([7, 7, 7]), [7, 7, 7])
        self.assertEqual(funcs.trois_grde_val([150, 800]), [800, 150])
        self.assertEqual(funcs.trois_grde_val([]), [])

if __name__ == '__main__':
    unittest.main()