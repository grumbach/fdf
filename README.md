# fdf

## Project Overview

This project is about creating a simplified 3D graphic representation of a relief landscape.
Except the parsing part and by using mlx, this project doesn't use MALLOC for its datastructures. 

* parallel projection in discomode
<img align="center" src="https://github.com/grumbach/fdf/blob/master/resources/fdf-42.png" width ="100%"/>
* isometric projection
<img align="center" src="https://github.com/grumbach/fdf/blob/master/resources/fdf-pyramid.png" width ="100%"/>
* big map with altitude and colors
<img align="center" src="https://github.com/grumbach/fdf/blob/master/resources/fdf-france.png" width ="100%"/>
* world map
<img align="center" src="https://github.com/grumbach/fdf/blob/master/resources/fdf-world.png" width ="100%"/>

## Installation

$> git clone https://github.com/grumbach/fdf.git && cd fdf && git clone https://github.com/grumbach/libft.git && make
<br>
$> ./fdf map.fdf

## Usage

* arrow keys to move the picture
* + - or mousewheel to zoom
* 1 and 2 to swich between parallel and isometric projections
* WASD to change 3D orientation
* spacebar to change colors
* tab to enter 'discomode'
