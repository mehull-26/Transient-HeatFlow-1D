# **1D Transient Heat Flow Solver**  

## **Overview**  
This program solves the **1D transient heat conduction equation** using three numerical methods:  
1. **Crank-Nicholson Method** (Implicit, second-order accurate)  
2. **Euler Implicit Method** (Backward Euler, first-order accurate)  
3. **Pure Implicit Method** (Fully implicit, stable for all time steps)  

The simulation models the heat distribution over time in a **1D rod** given initial and boundary conditions.  

---

## **Mathematical Formulation**  
The heat equation is given by:  

$$
\frac{\partial T}{\partial t} = \alpha \frac{\partial^2 T}{\partial x^2}
$$

where:  
- $T(x,t)$ = Temperature at position \( x \) and time \( t \)  
- $\alpha$ = Thermal diffusivity  

### **Numerical Methods Used**  
#### 1️⃣ Crank-Nicholson Method  
- **Implicit** and **second-order accurate** in both time and space.  
- Uses an **average of the implicit and explicit methods** for better stability and accuracy.  

#### 2️⃣ Euler Implicit Method  
- **Fully implicit**, first-order accurate in time.  
- Unconditionally stable, but introduces numerical diffusion.  

#### 3️⃣ Pure Implicit Method  
- Similar to Euler implicit but applied with different matrix formulations.  
- Suitable for handling **large time steps** without instability.  

---

## **Features**  
✅ Configurable **grid size** and **time step** for simulations.  
✅ Solves using **matrix inversion (Thomas algorithm for tridiagonal matrices)**.  
✅ Outputs **temperature profiles over time**.  

---

## **Installation & Usage**  

### **Dependencies**  
- Visual Studio Code

## **Example Output**  
The program generates:  
- **Temperature evolution plots** over time  


## **Future Improvements**  
🚀 Extend to **2D and 3D heat conduction**  
🧠 Implement **adaptive time-stepping**  
💻 Add **GPU acceleration** for larger simulations  

