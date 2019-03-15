timers = {}
Timer = {
  start: (name) => {
    const start = Date.now()
    timers.name = start
    return start
  },
  end: (name) => {
    console.log(name, Date.now() - timers.name)
  }
}