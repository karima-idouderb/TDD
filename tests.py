import funcs
import unittest

class TestFuncs(unittest.TestCase):
    def test_trois_grde_val(self):
        self.assertEqual(funcs.trois_grde_val([1, 2, 3, 4, 5]), [5, 4, 3])
        self.assertEqual(funcs.trois_grde_val([6, -1, 0, 9, 5]), [9, 6, 5])
        self.assertEqual(funcs.trois_grde_val([7, 7, 7]), [7, 7, 7])
        self.assertEqual(funcs.trois_grde_val([150, 800]), [800, 150])
        self.assertEqual(funcs.trois_grde_val([]), [])
    
    def test_est_premier(self):
        self.assertEqual(funcs.est_premier(2), True)
        self.assertEqual(funcs.est_premier(7), True)
        self.assertEqual(funcs.est_premier(8), False)
        self.assertEqual(funcs.est_premier(23), True)
        self.assertEqual(funcs.est_premier(1), False)
        self.assertEqual(funcs.est_premier(0), False)
        self.assertEqual(funcs.est_premier(-5), False)

    def test_est_suite_arith(self):
        self.assertEqual(funcs.est_suite_arith([1, 3, 5, 7, 9]), True)
        self.assertEqual(funcs.est_suite_arith([1, 2, 4, 8]), False)
        self.assertEqual(funcs.est_suite_arith([4, 4, 4]), True)
        self.assertEqual(funcs.est_suite_arith([8]), True)
        self.assertEqual(funcs.est_suite_arith([[10, 20]]), True)
        self.assertEqual(funcs.est_suite_arith([]), True)
        self.assertEqual(funcs.est_suite_arith([10, 5, 0, -5]), True)
        self.assertEqual(funcs.est_suite_arith([1.0, 1.3, 2.1]), False)
        self.assertEqual(funcs.est_suite_arith([1, 2.5, 4]), False)


if __name__ == '__main__':
    unittest.main()