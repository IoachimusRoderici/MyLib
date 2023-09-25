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

@pre |dir| = 1 && apertura ∈ [0, π]
@post |result| = 1 && ∠(dir, result) < apertura
"""
function random_direction_inside_cone(dir::Vector{Float64}, apertura::Real)
    #Basado en https://math.stackexchange.com/a/182936

    #Generar vectores ortonormales a dir:
    i = argmin(dir)
    u = normalize(I[1:3, i] × dir) #es perpendicular a dir y a un eje cartesiano.
    v = dir × u

    #Elejir ángulo aleatorio al rededor de dir:
    φ = rand(Uniform(0, 2*π))
    uv = cos(φ)*u + sin(φ)*v

    #Elegir una distancia a lo largo de la directríz:
    z = rand(Uniform(cos(apertura), 1))

    #Apertura del punto elegido:
    θ = acos(z)

    #Calcular el punto:
    z*dir + sin(θ)*uv    
end


end #MyRandomVectors