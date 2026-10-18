-- Smoke-test the original drawing/navigation callbacks with a small host fixture.
-- Run with Lua 5.4: lua tools/launcher/test-embedded-switch.lua headless/prosperoeden/ui/switch
local root = assert(arg[1], 'expected the embedded Switch theme folder')
local draws = 0
local app
local games = {}
for i=1,13 do games[i]={file="game-"..i,handle="game-"..i,name="Game "..i,remote=false} end
host = {
    query = function(name, args)
        if name == 'preferences' then return {reduce_motion=true, large_text=false, high_contrast=false, menu_bind={0,1,2,3}, theme='switch', mapping={1,0,3,2,4,5,6,7,10,12,8,9}} end
        if name == 'profiles' then return {} end
        if name == 'home' then return {last_file='', recents={}, status=''} end
        if name == 'choices' then return {resolution={},filter={},astc={},frame_gen_state=0} end
        if name == 'sources' then return {generation=1} end
        if name == 'library' then return {generation=1, scanning=false, games=games} end
        if name == 'status' then return {clock='12:00', room={phase=0}, controllers=1, version='v1.005.000', launch={stage='idle'}, update_status={phase=0}, save_sync={stage=0}, keyboard={ready=false}} end
        if name == 'measure' then return #(args.text or '') * (args.size or 24) * .5 end
        if name == 'launchers' then return {installed={{id='builtin',name='Canopy / Slate'},{id='switch-theme',name='Switch'}},active='switch-theme'} end
        return {}
    end,
    action = function() return {ok=true} end,
    draw = function() draws=draws+1; return true end,
}

local function frame(label,time)
    draws=0;app.update({dt=1/60,time=time});app.draw({time=time})
    assert(draws>20, label .. ' did not draw: '..tostring(draws))
    print(label, draws, 'draw calls')
end
for _,white in ipairs({false,true}) do
    local look=white and 'White' or 'Black'
    app = dofile(root .. '/main.lua')
    app.init({state={white=white},first_start=false,api_major=1,api_minor=1})
    frame(look..' HOME',1)
    for _=1,12 do app.input({key='right'}) end
    app.input({key='cross'});frame(look..' Library',1.5)
    app.input({key='circle'});app.input({key='down'})
    app.input({key='cross'});frame(look..' About',2)
    app.input({key='circle'})
    for _=1,4 do app.input({key='right'}) end
    app.input({key='cross'});frame(look..' Settings',3)
end
