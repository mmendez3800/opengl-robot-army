#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "Vector4.h"
#include "Globals.h"

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)

OBJObject::OBJObject(std::string filename, int flag) : Drawable()
{   
    parse(filename);

	if (flag == 2)
		scaleObject(14.72);

	else if (flag == 3)
		scaleObject(18.44);


	else if (flag == 4)
		scaleObject(14.26);

	centerObject();
}

OBJObject::~OBJObject()
{
	std::vector<Vector3>().swap(vertices);
	std::vector<Vector3>().swap(normals);
	std::vector<Vector3>().swap(colors);
	std::vector<Face>().swap(faces);
}

void OBJObject::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
	for (unsigned int i = 0; i < faces.size(); i++) {
		Face face = faces.at(i);

		for (int j = 0; j < 3; j++) {
			glNormal3fv((normals.at(face.normalIndices[j] - 1)).ptr());

			if (hasColor) {
				glColor3fv((colors.at(face.colorIndices[j] - 1)).ptr());
			}

			else {
				glColor3f(0.75, 0.75, 0.75);
			}

			glVertex3fv((vertices.at(face.vertexIndices[j] - 1)).ptr());
		}
	}
    
    glEnd();
    
    glPopMatrix();

	material.apply();
}

void OBJObject::update(UpdateData& data)
{
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens, f_1, f_2, f_3;
    std::string token;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        if(++lineNum % 10000 == 0)
            std::cout << "At line " << lineNum << std::endl;
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
		if (tokens.empty()){
			continue;
		}
        //If first token is a v then it gots to be a vertex
        if (tokens.at(0).compare("v") == 0)
        {
			hasColor = false;

            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));
            
            vertices.push_back(Vector3(x, y, z));

			if (tokens.size() > 4) {
				hasColor = true;

				float r = std::stof(tokens.at(4));
				float g = std::stof(tokens.at(5));
				float b = std::stof(tokens.at(6));

				colors.push_back(Vector3(r, g, b));
			}
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
			float xn = std::stof(tokens.at(1));
			float yn = std::stof(tokens.at(2));
			float zn = std::stof(tokens.at(3));

			Vector3 norm = Vector3(xn, yn, zn);
			vertexNormals.push_back(norm);

			norm = norm.normalize();
			normals.push_back(norm);
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face face;
            
            //Parse the face line
			f_1.clear();
			f_2.clear();
			f_3.clear();

			f_1 = split(tokens.at(1), '/', f_1);
			f_2 = split(tokens.at(2), '/', f_2);
			f_3 = split(tokens.at(3), '/', f_3);

			face.vertexIndices[0] = std::stof(f_1.at(0));
			face.colorIndices[0] = std::stof(f_1.at(0));
			face.normalIndices[0] = std::stof(f_1.at(2));

			face.vertexIndices[1] = std::stof(f_2.at(0));
			face.colorIndices[1] = std::stof(f_1.at(0));
			face.normalIndices[1] = std::stof(f_2.at(2));

			face.vertexIndices[2] = std::stof(f_3.at(0));
			face.colorIndices[2] = std::stof(f_1.at(0));
			face.normalIndices[2] = std::stof(f_3.at(2));
            
            faces.push_back(face);

			indices.push_back(face.vertexIndices[0] - 1);
			indices.push_back(face.vertexIndices[1] - 1);
			indices.push_back(face.vertexIndices[2] - 1);

			normIndices.push_back(face.normalIndices[0] - 1);
			normIndices.push_back(face.normalIndices[1] - 1);
			normIndices.push_back(face.normalIndices[2] - 1);
        }

		else if(tokens.at(0).compare("#") == 0)
        {
            //See the Wavefront Object format specification for details
			continue;
        }
        
    }
    
    std::cout << "Done parsing." << std::endl;
}

std::vector<Vector3>* OBJObject::getVertices()
{
	return &vertices;
}

std::vector<int>* OBJObject::getIndices()
{
	return &indices;
}

std::vector<Vector3>* OBJObject::getNormals()
{
	return &vertexNormals;
}

std::vector<int>* OBJObject::getNormIndices()
{
	return &normIndices;
}

void OBJObject::centerObject()
{
	std::vector<Vector3>* vertices = getVertices();

	Vector3 startVec = toWorld * vertices->at(0);
	//Vector3 startVec = vertices->at(0);

	float left = startVec[0];
	float right = startVec[0];
	float top = startVec[1];
	float bottom = startVec[1];
	float front = startVec[2];
	float back = startVec[2];

	std::vector<Vector3>::iterator itr = vertices->begin();

	while (itr != vertices->end())
	{
		Vector3 vec = (toWorld * (*itr++).toVector4(1.0)).toVector3();
		//Vector3 vec = *itr++;

		left = std::min(vec[0], left);
		right = std::max(vec[0], right);
		top = std::max(vec[1], top);
		bottom = std::min(vec[1], bottom);
		front = std::max(vec[2], front);
		back = std::min(vec[2], back);
	}

	float xCenter = (right + left) / 2;
	float yCenter = (top + bottom) / 2;
	float zCenter = (front + back) / 2;

	Matrix4 translate;
	translate.makeTranslate(-xCenter, -yCenter, -zCenter);

	toWorld = translate * toWorld;
}

void OBJObject::scaleObject(float factor)
{
	std::vector<Vector3>* vertices = getVertices();

	Vector3 startVec = toWorld * vertices->at(0);
	//Vector3 startVec = vertices->at(0);

	float left = startVec[0];
	float right = startVec[0];
	float top = startVec[1];
	float bottom = startVec[1];

	std::vector<Vector3>::iterator itr = vertices->begin();

	while (itr != vertices->end())
	{
		Vector3 vec = (toWorld * (*itr++).toVector4(1.0)).toVector3();
		//Vector3 vec = *itr++;

		left = std::min(vec[0], left);
		right = std::max(vec[0], right);
		top = std::max(vec[1], top);
		bottom = std::min(vec[1], bottom);
	}

	float lengthX = (right - left) / 2;
	float lengthY = (top - bottom) / 2;
	float length = lengthX;

	Matrix4 scale;
	scale.makeScale(factor * tan(30 * M_PI / 180) / length);

	toWorld = toWorld * scale;
}

std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
