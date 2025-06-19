
impl ship
- position ship in center of screen
- draw ship as a triangle
- turn ship using left and right arrow keys
- move ship forward with up arrow key that accelerates the ship
- make sure wrap the canvas (going offscreen on one side moves you to the other side of the screen)

impl ship lasers
- pressing the space button triggers a laser to shoot from the ship
- lasers can wrap around the screen?
- lasers can collide with asteroids
- splitting an asteroid increases score

impl asteroid
- render asteroid as a circle to start
- position asteroids around the ship
- asteroids should have random vector

impl collision detection
- ship and asteroid --> game over
- laser and asteroid ---> increases score

impl UI
- draw score
- draw pause button to pause game loop
- draw quit button to quit game
- impl game over screen
