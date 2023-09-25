using Plots
using LinearAlgebra

include("../MyRandomVectors.jl")
using .MyRandomVectors


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


#Test random_direction_inside_cone:
θ = 0.6
dir = normalize([1, 0.2, 0.1])
puntos = [random_direction_inside_cone(dir, θ) for i in 1:400]
X = getindex.(puntos, 1)
Y = getindex.(puntos, 2)
Z = getindex.(puntos, 3)

plot3 = scatter(X, Y, xlim=(-1,1), ylim=(-1,1), aspect_ratio=1, markersize=2, xlabel="x", ylabel="y", title="vista superior")
plot4 = scatter(Y, Z, xlim=(-1,1), ylim=(-1,1), aspect_ratio=1, markersize=2, xlabel="y", ylabel="z", title="vista frontal")
scatter!(plot3, [dir[1]], [dir[2]], markercolor=:red)
scatter!(plot4, [dir[2]], [dir[3]], markercolor=:red)
gui(plot(plot1, plot2, plot3, plot4, layout=(2,2), size=(1000, 1000)))

modulos = norm.(puntos)
if any(modulos .≉ 1)
    println("random_direction_inside_cone: Hay normas distintas de 1.")
end

angulos = [acos(punto⋅dir) for punto in puntos]
if any(angulos .> θ)
    println("random_direction_inside_cone: Hay ángulos más grandes que θ.")
end


show("Enter para Terminar.")
readline()