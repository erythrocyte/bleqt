Dimensionless
========

The following dimensionless parameters will be defined:

    .. math::
        \bar{p} = \dfrac{p - p_c}{p_c - p_w}, \\
        \bar{r, z} = \dfrac{r, z}{R}, \\
        \bar{u} = \dfrac{u}{u_0}, u_0 = \dfrac{k}{\mu_w}\dfrac{p_c - p_w}{R}, \\
        \bar{u_f} = \dfrac{u_f}{u_f^0}, u_f^0 = \dfrac{k_f}{\mu_w}\dfrac{p_c - p_w}{R}, \\
        \bar{t} = \dfrac{t}{t_0}, t_0 = \dfrac{m_f R}{u_f^0}, \\
        \bar{q} = \dfrac{q}{q_0}, q_0 = R^2 u_f^0.

After applying dimensionless variables equation for pressure in reservoir will not change it's form. 

Equations for pressure and saturation in fracture become (dimensionless sign is gone)

    - pressure:
        .. math::
            \triangledown_r u_f + \dfrac{1}{2M} \left.u_z\right|_{\Gamma_f(-\delta)}^{\Gamma_f(\delta)} = 0, 
            \;\;\; M = \dfrac{\delta k_f}{R k}.

    - saturation:
        .. math::
            \dfrac{\partial s_f}{\partial t} + 
            \triangledown_r \left(f(s_f)u_f\right) + \dfrac{1}{2M} \left.\left(f(s)u_z\right)\right|_{\Gamma_f(-\delta)}^{\Gamma_f(\delta)} = 0.


