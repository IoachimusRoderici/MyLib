using Plots
using LinearAlgebra

include("MyRandomVectors.jl")
using .MyRandomVectors

#=
#Test random_direction in 2D:
puntos = [random_direction(2) for i in 1:100]
X = getindex.(puntos, 1)
Y = getindex.(puntos, 2)

plot1 = scatter(X, Y; aspect_ratio=1, title="random_direction(2)")


#Test random_point_inside_sphere in 2D:
puntos = [random_point_inside_sphere(2, 1) for i in 1:900]
X = getindex.(puntos, 1)
Y = getindex.(puntos, 2)

plot2 = scatter(X, Y; aspect_ratio=1, title="random_point_inside_sphere(2, 1)", markersize=2)


#Show plots and wait:
gui(plot(plot1, plot2, layout=(1,2), size=(1000, 500)))

show("Enter para Continuar.")
readline()=#

#Test random_direction_inside_cone:
θ = 0.6
dir = Float64[1, 0, 0]
puntos = [random_direction_inside_cone(dir, θ) for i in 1:300]
X = getindex.(puntos, 1)
Y = getindex.(puntos, 2)
Z = getindex.(puntos, 3)

plot1 = scatter(X, Y, xlim=(-1,1), ylim=(-1,1), aspect_ratio=1, markersize=2, title="vista superior")
plot2 = scatter(Y, Z, xlim=(-1,1), ylim=(-1,1), aspect_ratio=1, markersize=2, title="vista frontal")
gui(plot(plot1, plot2, layout=(1,2), size=(1000, 500)))


for punto in puntos
    if punto⋅dir > θ
        println("θ=", punto⋅dir)
    end
end

show("Enter para Continuar.")
readline()