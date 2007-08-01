gloox = require('gloox')

function onRun()
end

function onStatusChange(data)
end

events:subscribe('Session', 'StatusChange', onStatusChange)
events:subscribe('Core', 'Run', onRun)
