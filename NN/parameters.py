import numpy as np


class HyperParameters:
    def __init__(self, EtaParam, LambdaParam, AlphaParam):
        self.Eta = EtaParam
        self.Lambda = LambdaParam
        self.Alpha = AlphaParam

    def __repr__(self):
        return f"HyperParams({self.Eta},{self.Lambda},{self.Alpha})"


class Grid:
    def __init__(
        self, eta_1, eta_2, lambda_1, lambda_2, alpha_1, alpha_2, steps1, steps2, steps3
    ):
        self.Grid = np.array(
            [
                HyperParameters(
                    eta_1 + i * (eta_2 - eta_1) / steps1,
                    lambda_1 + j * (lambda_2 - lambda_1) / steps2,
                    alpha_1 + k * (alpha_2 - alpha_1) / steps3,
                )
                for i in range(int(steps1))
                for j in range(int(steps2))
                for k in range(int(steps3))
            ],
            dtype=HyperParameters,
        )
