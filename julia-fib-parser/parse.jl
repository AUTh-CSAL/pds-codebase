using DelimitedFiles
using Plots
using Statistics

# parse output of execution
M = readdlm("./run.log", ',', Float64, skipstart=1);

# select plotly as backend and open figure
plotly(ticks=:native)
plt = plot();
# Binet
F(n) = convert( Int64, round(((1+sqrt(big(5)))^n-(1-sqrt(big(5)))^n)/(sqrt(big(5))*big(2)^n),digits=0))

# draw different curve for differet number of processors
npList = unique(M[:,1]);
for i in 1:length(npList)
    ind = npList[i] .== M[:,1];
    x = M[ind,2]
    @assert all( (F.(x) - M[ind,3]) .== 0 )
    y = vec(mean(M[ind,5:end], dims=2))
    plot!(plt, x, y, label="np = $(npList[i])",
          markershape=:xcross)
end


# fix plot attributes & display
plot!(title = "Time to compute fib(n)", xlabel = "n", ylabel = "time (sec)",
      xscale = :log, yscale = :log)
display(plt);
