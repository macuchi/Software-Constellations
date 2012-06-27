#pragma once

#include "ofMain.h"
#include "ofVectorMath.h"
#include "ofxOpenCv.h"
#include "MSAShape3D.h"
#define MAX_AREAS 3
#define MAX_VERTEX 15
class Area
{
    public:
	ofPoint * vertices, *v_triang;
	ofPoint  rect;
	int vCapturados,width,height,r,g,b;
	bool capturando,es_poligono;
	MSA::Shape3D triangulo;
	Area()
	{
		vertices = new ofPoint[3];
		v_triang = new ofPoint[3];
		triangulo.reserve(3);
		vCapturados=0;
		capturando = 1;
		width = 0;
		height = 0;
		r = ofRandom(100,255);
		g = ofRandom(50,100);
		b = ofRandom(100,255);
	}
	bool capturar(int x,int y)
	{
		vertices[vCapturados].x = x;
		vertices[vCapturados].y = y;
		vCapturados++;
		cout<<"Vertice "<<vCapturados<<" Capturado. X = "<<x<<" Y = "<<y<<endl;
		if(vCapturados==3)
		{
			capturando = 0;
			es_poligono = false;
			int xMenor = MIN(vertices[1].x,vertices[2].x);
			rect.x = MIN(vertices[0].x,xMenor);
			int xMayor = MAX(vertices[1].x,vertices[2].x);
			width = MAX(vertices[0].x,xMayor)-rect.x;
			int yMenor = MIN(vertices[1].y,vertices[2].y);
			rect.y = MIN(vertices[0].y,yMenor);
			int yMayor = MAX(vertices[1].y,vertices[2].y);
			height = MAX(vertices[0].y,yMayor)-rect.y;

			v_triang[0] = ofPoint(vertices[0].x+320,vertices[0].y,0);
			v_triang[1] = ofPoint(vertices[1].x+320,vertices[1].y,0);
			v_triang[2] = ofPoint(vertices[2].x+320,vertices[2].y,0);
		}
		return capturando;
	}
	void caprutar_poli(int x,int y)
	{
		if(vCapturados<MAX_VERTEX)
		{
			vertices[vCapturados].x = x;
			vertices[vCapturados].y = y;
			v_triang[vCapturados] = ofPoint(vertices[vCapturados].x+320,vertices[vCapturados].y);
			vCapturados++;
			cout<<"Vertice "<<vCapturados<<" X = "<<x<<" Y = "<<y<<endl;
		}
	}
	void calcular_textura()
	{
		float xmayor = vertices[0].x;
		float ymayor = vertices[0].y;
		float xmenor = vertices[0].x;
		float ymenor = vertices[0].y;
		cout<<xmayor<<endl<<ymayor<<endl<<xmenor<<endl<<ymenor<<endl;
		
		for(int j=1;j<vCapturados;j++)
		{
			xmayor = MAX(xmayor,vertices[j].x);
			ymayor = MAX(ymayor,vertices[j].y);
			xmenor = MIN(xmenor,vertices[j].x);
			ymenor = MIN(ymenor,vertices[j].y);
		}
		width = xmayor-xmenor;
		height = ymayor-ymenor;
		rect.x = xmenor;
		rect.y = ymenor;
	}
	void pintar()
	{
		ofImage imagen;
		imagen.grabScreen(rect.x,rect.y,width,height);
		if(!es_poligono)
		{
						///nuevo///
		
			triangulo.begin(GL_TRIANGLES);
			glNormal3d(0,0,-1);
			triangulo.setTexCoord(vertices[0].x-rect.x,vertices[0].y-rect.y);
			triangulo.addVertex(v_triang[0].x,v_triang[0].y);

			triangulo.setTexCoord(vertices[1].x-rect.x,vertices[1].y-rect.y);
			triangulo.addVertex(v_triang[1].x,v_triang[1].y);

			triangulo.setTexCoord(vertices[2].x-rect.x,vertices[2].y-rect.y);
			triangulo.addVertex(v_triang[2].x,v_triang[2].y);

			imagen.bind();
			triangulo.end();
			imagen.unbind();
		}
		else
		{
			triangulo.begin(GL_POLYGON);
			glNormal3d(0,0,-1);
			for(int i=0;i<vCapturados;i++)
			{
				triangulo.setTexCoord(vertices[i].x-rect.x,vertices[i].y-rect.y);
				triangulo.addVertex(v_triang[i].x,v_triang[i].y);
			}
			imagen.bind();
			triangulo.end();
			imagen.unbind();
		}
		imagen.~ofImage_();
	}
	void pintar_lineas(bool m)
	{
		ofSetColor(r,g,b);
		if(!es_poligono)
		{
			ofLine(vertices[0],vertices[1]);
			ofLine(vertices[1],vertices[2]);
			ofLine(vertices[2],vertices[0]);
			if(m)
			{
				ofCircle(v_triang[0],3);
				ofCircle(v_triang[1],3);
				ofCircle(v_triang[2],3);
			}
		}
		else
		{
			for(int i=0;i<vCapturados;i++)
			{
				if(m)
					ofCircle(v_triang[i],3);
				if(i>0)
					ofLine(vertices[i-1],vertices[i]);
			}
			ofLine(vertices[vCapturados-1],vertices[0]);
		}
	}

};
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		  
		ofVideoGrabber 		vidGrabber;
		int camWidth,camHeight,nAreas,aSeleccion,pSeleccion,rad_seleccion;
		Area * areas;
		bool creando,creando_poli,modificar,modificar_area;

};

