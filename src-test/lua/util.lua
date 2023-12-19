local util = {}

util.inspect = require("inspect")

util.log = function(...)
  local result = ""
  local nb_args = select("#", ...)

  for i = 1, nb_args, 1 do
    local arg = select(i, ...)

    if i == 1 and type(arg) == "string" then
      result = result .. arg
    elseif type(arg) == "userdata" then
      result = result .. " " .. tostring(arg)
    else
      result = result .. " " .. util.inspect(arg)
    end
  end

  print(result)
end

local function sep(label, new_line)
  local count = math.max(0, 80 - label:len())
  print(label .. string.rep("-", count) .. (new_line and "\n" or ""))
end

util.make_test = function(name, func)
  return function()
    sep("test_" .. name .. "_begin")
    func()
    sep("test_" .. name .. "_end", true)
  end
end

return util
