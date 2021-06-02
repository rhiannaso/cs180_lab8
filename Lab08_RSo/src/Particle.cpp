//
// sueda - geometry edits Z. Wood
// 3/16
//

#include <iostream>
#include "Particle.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Texture.h"


float randFloat(float l, float h)
{
	float r = rand() / (float) RAND_MAX;
	return (1.0f - r) * l + r * h;
}

Particle::Particle(vec3 start) :
	charge(1.0f),
	m(1.0f),
	d(0.0f),
	x(start),
	v(0.0f, 0.0f, 0.0f),
	lifespan(1.0f),
	tEnd(0.0f),
	scale(1.0f),
	color(1.0f, 1.0f, 1.0f, 1.0f)
{
}

Particle::~Particle()
{
}

void Particle::load(vec3 start)
{
	// Random initialization
	rebirth(0.0f, start);
}

/* all particles born at the origin */
void Particle::rebirth(float t, vec3 start)
{
	charge = randFloat(0.0f, 1.0f) < 0.5 ? -1.0f : 1.0f;	
	m = 1.0f;
  	d = randFloat(0.0f, 0.02f);
	x = start;
	v.x = randFloat(-0.25f, 0.25f);
	v.y = randFloat(0.025f, 0.4f);
	v.z = randFloat(-0.25f, 0.25f);
	lifespan = randFloat(100.0f, 200.0f); 
	tEnd = t + lifespan;
	scale = randFloat(0.2, 1.0f);
   	color.r = randFloat(0.0f, 0.1f);
   	color.g = randFloat(0.0f, 0.1f);
   	color.b = randFloat(0.25f, 0.5f);
	color.a = 1.0f;
}

void Particle::update(float t, float h, const vec3 &g, const vec3 start)
{
	if(t > tEnd) {
		rebirth(t, start);
	}

	//very simple update
	// x += h*v;
    // x.x = h + (v.x*t) + (0.5*(g.x)*t*t);
    // x.y = h + (v.y*t) + (0.5*(g.y)*t*t);
    // x.z = h + (v.z*t) + (0.5*(g.z)*t*t);
    x.x += (0.07*(h + (v.x*t) + (0.5*(g.x)*t*t)));
    x.y += (0.07*(h + (v.y*t) + (0.5*(g.y)*t*t)));
    x.z += (0.07*(h + (v.z*t) + (0.5*(g.z)*t*t)));
	//To do - how do you want to update the forces?
	color.a = (tEnd-t)/lifespan;
}
