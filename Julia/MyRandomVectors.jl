module MyRandomVectors

using LinearAlgebra: normalize

export random_direction
export random_point_in_sphere


"""
    random_direction(dims)

Devuelve un vector unitario aleatorio, con una distribución
uniforme en la superficie de la esfera unitaria.

dims indica el número de dimensiones.
"""
function random_direction(dims::Integer)::Vector{Float64}
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
    random_point_in_sphere(dims, radius)

Devuelve un vector aleatorio con distribución homogénea en el 
volumen de una esfera de radio `radius` en `dims` dimensiones.
"""
function random_point_in_sphere(dims::Integer, radius::Real)::Vector{Float64}
    random_direction(dims) * radius * rand()^(1/dims)
end


end #MyRandomVectors