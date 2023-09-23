using Plots

include("MyRandomVectors.jl")
using .MyRandomVectors

#Test random_direction in 2D:
puntos = [random_direction(2) for i in 1:100];
X = getindex.(puntos, 1);
Y = getindex.(puntos, 2);

plot1 = scatter(X, Y; aspect_ratio=1, title="random_direction(2)")


#Test random_point_in_sphere in 2D:
puntos = [random_point_in_sphere(2, 1) for i in 1:900];
X = getindex.(puntos, 1);
Y = getindex.(puntos, 2);

plot2 = scatter(X, Y; aspect_ratio=1, title="random_point_in_sphere(2, 1)", markersize=2)

#Show plots and wait:
gui(plot(plot1, plot2, layout=(1,2), size=(1000, 500)))

show("Enter para terminar.")
readline()
