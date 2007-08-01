dofile('scripts/events.lua')
dofile('scripts/log.lua')
dofile('scripts/plugins.lua')
dofile('scripts/utils.lua')

core = {}

function core:run()
  events:fire('Core', 'Started')
  events:fire('Session', 'StatusChange', {status = 'available', msg = ''})
  while 1 do
    events:fire('Core', 'Run')
    sleep(10)
  end
end

core:run()

events:fire('Core', 'PreShutdown')
