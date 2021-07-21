# Lab 14

In this lab we simulate the motion of planets and other bodies
in our solar system.
When we measure positions in astronomical units (AU), time in days (d) and masses in units of *m*<sub>sun</sub> the equations are

<p align="center">
<img src="stuffy_stuff/eq1.png" width="300">
</p>

where G = 2.9592208286e-4.

The total energy in the system is 

<p align="center">
<img src="stuffy_stuff/eq2.png" width="400">
</p>

---
In order to solve the equations, we use the Störmer-Verlet scheme,
where one time-step is
<p align="center">
<img src="stuffy_stuff/eq3.png" width="270">
</p>
where 
<p align="center">
<img src="stuffy_stuff/eq4.png" width="270">
</p>

---

Initial positions and velocities (2nd Dec, 2019) and masses are provided along
with the starter code.

The file `iv.txt` contains the information for the first five planets
1. Sun
2. Mercury
3. Venus
4. Earth
5. Mars

The starter code already takes care of reading initial values from a file. In this file the first line is the number of objects *N*. Then follow *N* lines with the masses of the object. After that *3N* lines with the initial positions x<sub>i</sub>, y<sub>i</sub>, z<sub>i</sub> for every body. The last block of 3N lines then are the initial velocities vx<sub>i</sub>, vy<sub>i</sub>, vz<sub>i</sub> for all bodies.

The data is read into three arrays `M, r, v`.
 
---

### Tasks

* Write functions `step_v` and `step_r` that calculate the new velocities and
  positions. 
* Write a function `energy` that calculates the energy after every time-step
* After every time-step print the **time**, all **coordinates** and the **energy**
  as a **line** into an output file.
* Assuming your output file contains in columns 2,3,4 the positions
  x<sub>1</sub>, y<sub>1</sub>, z<sub>1</sub> (which would be the sun)m
  then you can plot the trajectory in gnuplot via
  ```
  splot 'data' u 2:3:4
  ```
  If you want to plot all trajectories at once and follow the above file
  layout, then you can plot all trajectories at once via
  ```
  splot for [i=0:4] "data" u 3*i+2:3*i+3:3*i+4 
  ```
  If you want to get rid of the legend, put 
  ``` 
  unset key
  ``` 
  once into gnuplot before calling `splot`:
  ``` 
  unset key
  set style data line
  splot for [i=0:4] "data" u 3*i+2:3*i+3:3*i+4 
  ```  


---
The file `iv2.txt` contains initial conditions for some more bodies. These are:
1. Sun
2. Mercury
3. Venus
4. Earth
5. Mars
6. Jupiter
7. Saturn  
8. Uranus 
9. Neptune
10. Pluto
11. Moon
12. Ceres
13. Io
14. Europa 
15. Ganymede
16. Phobos
17. Deimos
18. Charon
19. Nix
20. Kerberos
21. Pallas
22. Vesta
23. Juno
24. Metis
25. Hygiea
26. Euphrosyne