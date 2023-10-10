This is the firmware for Node Rover. Check [here](https://www.printables.com/model/523293-node-robot-platform-smars-inspired-using-esp8266) for more.

Note: This project required pior knowledge of compiling PlatformIO project and basic networking skill (find device IP)

Installation steps:
1. Compile project with PlatformIO (VSCode)
2. Flash compiled firmware to NodeMCU 8266
3. Using your phone to connect to "ESP_Robot" wifi, password: `12345678` and connect the rover to your wifi network
4. Go to your Wifi router and find your rover's IP
5. Modify `src/webcontroller.html`, find `robot_ip` variable and replace the `192.168.1.4` with your rover's IP.
6. Recompile and flash firmware to your NodeMCU again.
7. Using browser on your computer, go to `http://<your-rover-ip>`

<!-- (all the following step is due to PlatformIO not correctly identify `embed_txtfiles` so we have to do it manually)
6. Go to [this site](https://www.toptal.com/developers/html-minifier), paste html content to `Input HTML` and press `Minify`. Then copy `Minified HTML Output` to clipboard.
7. Go to [this site](https://codebeautify.org/minify-html), paste `Minified HTML Output` to the text area in the left and press `Minify HTML`, copy the minify content of the right to clipboard.
8.  -->