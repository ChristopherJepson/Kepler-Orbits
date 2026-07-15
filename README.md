# Kepler-Orbits: C++ N-Body Gravity Simulation

**Kepler-Orbits** is a high-fidelity Newtonian physics simulation built from the ground up in **Unreal Engine 5** using **C++**. Moving beyond standard engine-physics components, this project implements a custom gravitational system where multiple celestial bodies interact dynamically in a true N-body environment.

## 🚀 Project Overview
While previous work (such as *Space-Survivor*) focused on shipping gameplay with integrated CI/CD pipeline tooling in Unity, **Kepler-Orbits** represents a deliberate shift into UE5 C++ systems engineering — building custom engine components from scratch rather than consuming existing ones. 

### Key Features:
* **Custom C++ Physics:** A specialized `UOrbitalMovementComponent` that handles velocity, acceleration, and position updates manually in the `Tick` loop.
* **True N-Body Interaction:** Planets exert gravitational force on every other object tagged as an `OrbitalBody`, leading to emergent orbital decay, elliptical paths, and multi-body interactions.
* **Real-time Force Visualization:** Integrated `DrawDebugLine` helpers to visualize the active gravitational "tethers" between all bodies in the simulation.
* **Advanced VFX Integration:** Leveraged Niagara Location-Based Ribbons to track and persist orbital paths as geometric rings in space.

---

<div align="center">
  <img src="https://i.ibb.co/8L6kfPHH/Kepler-Orbits-0-0-6-Screen-Shot.png" width="100%" height="auto" alt="Kepler Orbits 0 0 6 Screen Shot" border="0">
</div>

---

## 🛠 Technical Challenges & Solutions

### 1. The Perpendicular Velocity Problem
**Challenge:** Early iterations saw planets either flying off into the void or falling directly into the sun. 
**Solution:** I implemented a mass-based orbital velocity calculation. By placing planets on the Y-axis and applying a calculated perpendicular velocity on the X-axis, I achieved stable orbits.
* **Formula:** $V = \sqrt{\frac{G \times M_{star}}{R}}$

### 2. Achieving "Neptune" Saturation
**Challenge:** Standard Lit materials often resulted in a "grey plastic" look for dark celestial bodies due to surface specular reflections and tone mapping.
**Solution:** I transitioned the planetary master material to an **Unlit Shading Model**. By feeding the color data into the **Emissive Color** slot and using a **Power** node to deepen the hue, I achieved rich, saturated blues that maintain their hue without washing out to white.

### 3. Repository Hygiene for Professional Environments
**Challenge:** Unreal projects generate gigabytes of temporary data that clutter version control.
**Solution:** I configured a strict `.gitignore` to exclude engine-generated binaries, intermediate folders, and proprietary marketplace content. This ensures the repository remains focused on the original source code and custom architectural logic — a foundational requirement for reliable CI/CD pipeline operation on UE5 projects, where unmanaged binary artifacts can corrupt build reproducibility.

---

## 📈 Engineering Evolution & Optimization
The current system operates on an $O(n^2)$ complexity, where every planet checks every other actor every frame. 
* **Scalability Path:** For a production-scale environment (thousands of bodies), I have explored transitioning this logic to **Unreal’s Mass Entity (ECS) framework**. This would move the simulation from an Object-Oriented approach to a Data-Oriented Design (DOD) to significantly reduce CPU overhead.

---

## 📂 Directory Structure
* **`/Source`**: Custom C++ classes including the core `OrbitalMovementComponent` logic.
* **`/Content`**: Custom master materials, planetary instances, and Niagara VFX systems.
* **`/Config`**: Project-specific input and engine configurations.

---

## 📝 About the Author

**Christopher Jepson**  
*Build & Tools Engineer*

Systems-focused engineer working at the intersection of game engine 
architecture and build pipeline automation. Kepler-Orbits represents 
the C++ and UE5 systems engineering layer of a broader portfolio spanning 
Unity CI/CD pipelines, UE5 editor tooling, and AI-integrated development 
workflows.

[LinkedIn](https://www.linkedin.com/in/christopher-jepson-310a84308) | 
[Email](mailto:christopher.j.jepson@gmail.com) | 
[GitHub](https://github.com/ChristopherJepson)
