Equations
=====

Domain is a cylinder :math:`D = [rw, R] * [0, 2\pi] * [-L, L]`, which includes fracture :math:`D_f = [rw, R] * [0, 2\pi] * [-\delta, \delta]`.

Reservoir:
    - pressure:
        .. math::
            \text{div}(u) = 0, \;\;\;  u = -\sigma(\boldsymbol{x}, s) \cdot \triangledown p, \;\;\;
            \sigma = k(\boldsymbol{x}) / \mu(s).

    here :math:`\boldsymbol{x}` is a point, :math:`\mu(s) -` fluid viscosity, :math:`u -` flow rate, :math:`s -` (water) saturation, 
    :math:`k -` - permeability, :math:`\sigma -` transmissibility of fluid.
    
    Functions :math:`\mu(s), f(s)` defined from relative permeability degree functions

        .. math::
            \dfrac{1}{\mu(s)} = \dfrac{\phi(s)}{\mu_w}, \;\;\;
            \phi(s) = k_w(s) + k_{\mu} k_o(s), \;\;\;
            k_{\mu} = \dfrac{\mu_w}{\mu_o}, \\
            k_w(s) = s^N, \;\;\; k_o(s) = \left(1-s\right)^N.
    
    here  :math:`k_w -` relative permeability of water, :math:`k_o -` relative permeability of oil, 
    :math:`\mu_w -` water viscosity, :math:`\mu_o -` oil viscosity.

    .. note::
         Note that irreducible water and oil saturations are equal to 0.

    - saturation:
        .. math::
            s = const. 

Fracture:
    .. :label: eq:aver_fract ..
    Let us define average value over pressure variables    

    .. math::            
        \left<\cdot\right>_f = \dfrac{1}{2\delta} \int_{-\delta}^{\delta} \left(\cdot\right)dz.
        :label: averfract

    - pressure:
        .. math::            
            \text{div}(u_f) = 0, \;\;\;  u_f = -\sigma_f(s_f) \cdot \triangledown p_f, \;\;\;
            \sigma_f = k_f / \mu(s).
          :label: pressfract

    here :math:`u_f -` flow rate in fracture, :math:`s -` (water) saturation, 
    :math:`k_f -` constant fracture permeability.

    Assume that 

    .. math::
        <u_f>_r \approx -\dfrac{k_f}{\mu}\triangledown <p_f>.

    If we integrate equation :eq:`pressfract` from :math:`-\delta` to :math:`\delta` using :eq:`averfract` 
    and consider that we get (average signs :math:`<>` are gone)

    .. math::
        \triangledown_r u_f + \dfrac{1}{2\delta} \left.u_z\right|_{\Gamma_f(-\delta)}^{\Gamma_f(\delta)} = 0.
        :label: pressfractaver

    The last member in :eq:`pressfractaver` defines the flow from reservoir to fracture from bounds :math:`\Gamma_f(-\delta), \Gamma_f(\delta)`.

    - saturation:
        .. math::
            m_f \dfrac{\partial s_f}{\partial t} + 
            \triangledown_r \left(f(s_f)u_f\right) + \dfrac{1}{2\delta} \left.\left(f(s)u_z\right)\right|_{\Gamma_f(-\delta)}^{\Gamma_f(\delta)} = 0, \;\;\;
            f(x) = \dfrac{k_w(x)}{\phi(x)},
            :label: saturfract

        here :math:`f(x) -` Backley-Leverette function.


Conditions:
    - boundary:
        .. math::
            
            \Gamma_w^f \in [r_w, rw]*[0,2\pi]*[-\delta, \delta]: p = p_w, \\
            \Gamma_T \in [r_w, R]*[0, 2\pi]*[\pm L,\pm L]: p = p_c, \\
            \Gamma_w \in [r_w, rw]*[0,2\pi]*[-L, L]/[-\delta, \delta]: u_n = -\sigma \dfrac{\partial p}{\partial n} = 0, \\
            \Gamma_B \in [R, R]*[0, 2\pi]*[-L, L]: u_n = 0, \\
            \Gamma_f \in [R, R]*[0, 2\pi]*[\pm \delta, \pm \delta]: p = p_f, u = u_f, s = s_0.

    - initial:
        .. math::
            s = s_0 = const, \\
            s_f = s_f^0.


Well flow rate:
    - from fract to well:  
        .. math::
            q = \int_{\Gamma_w^f} u_f d\Gamma = 4\pi r_w \delta u_f.


    - from reservoir to fract:
        .. math::
            q = \int_{\Gamma_T} u d\Gamma.

    