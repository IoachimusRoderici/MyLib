module MyRandomVectors

using LinearAlgebra
using Distributions: Uniform, Exponential

export random_direction
export random_point_inside_sphere
export random_direction_inside_cone


"""
    random_point_in_sphere(dims, radius)

Devuelve un vector aleatorio con distribución homogénea en el 
volumen de una esfera de radio `radius` en `dims` dimensiones.
"""
function random_point_inside_sphere(dims::Integer, radius::Real)
    random_direction(dims) * radius * rand()^(1/dims)
end


"""
    random_direction(dims)

Devuelve un vector unitario aleatorio, con una distribución
uniforme en la superficie de la esfera unitaria.

dims indica el número de dimensiones.
"""
function random_direction(dims::Integer)
    #Take a random normal vector:
    V = randn(dims)

    #Make shure it's not the null vector:
    while iszero(V)
        V = randn(dims)
    end

    #Normalize it:
    normalize(V)
end

"""
    random_direction_inside_cone()

Devuelve un vector unitario aleatorio con distribución uniforme
dentro del cono con la directríz dada por dir y el semi-ángulo
dado por apertura.
"""
function random_direction_inside_cone(dir::Vector{Float64}, apertura::Real)

    #Primero generar una dirección aleatoria dentro
    #del cono centrado en el eje z:
    z = rand(Uniform(cos(apertura), 1))
    k = sqrt(1 - z^2)  #distancia perpendicular a z
    φ = rand(Uniform(0, 2*π))
    vec = [k*cos(φ), k*sin(φ), z]

    #Y después rotarlo 
    eje_de_rotacion = [0, 0, 1.0] × dir
    cosθ = dir ⋅ [0, 0, 1.0] #ángulo de rotación
    θ = acos(cosθ)
    sinθ = sin(θ)

    vec_rotado = cosθ*vec + sinθ*(eje_de_rotacion×vec) + (1-cosθ)*(eje_de_rotacion⋅vec)*eje_de_rotacion

    normalize(vec_rotado)
end


end #MyRandomVectors