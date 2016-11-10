lrterminal.conf = function(settings)
  -- set the configuration
  -- terminal width
  settings.width = 40
  -- terminal height
  settings.height = 20
end

local tick = 0
local xPos = 0

lrterminal.init = function()
  -- Initialize function
  -- Note: The lrterminal.terminal() function is not valid before this has been called.
end

lrterminal.deinit = function()
  -- Deinitialize function
end

lrterminal.update = function(deltaTime)
  -- Update game logic here
  tick = tick + deltaTime
  if (tick > 0.05) then
    tick = 0
    xPos = xPos + 1
    if (xPos > 40) then
      xPos = 0
    end
  end
  -- Update the root console
  lrterminal.log(lrterminal.LogLevel_INFO, "Lua: "..deltaTime.."\n")
  local rootConsole = lrterminal.terminal():getRootConsole()
  local style = rootConsole:getDefaultStyle()
  style:setBackground(lrterminal.Color_darkBlue)
  style:setForeground(lrterminal.Color_yellow)
  style:setAlignment(lrterminal.Alignment_CENTER)
  rootConsole:setDefaultStyle(style)
  rootConsole:clear()
  rootConsole:print(xPos, 10, "Hello World from Lua.")
end
