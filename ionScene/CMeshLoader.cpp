#include "CMeshLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdio>
#include <sys/stat.h>

#include <limits>

#pragma warning(disable: 4996)

std::map<std::string, CMesh *> CMeshLoader::LoadedMeshes;
std::string CMeshLoader::MeshDirectory = "../Media/Models/";

static long filelength(int f)
{
    struct stat buf;

    fstat(f, &buf);

    return(buf.st_size);
}

// TODO: Rewrite this horrendous pile of C nonsense
CMesh * const CMeshLoader::load3dsMesh(std::string const & fileName, bool const useCache)
{
	if (useCache)
	{
		std::map<std::string, CMesh *>::iterator it = LoadedMeshes.find(fileName);

		if (it != LoadedMeshes.end())
		{
			return it->second;
		}
	}

    int i; //Index variable

    FILE *l_file; //File pointer

    unsigned short l_chunk_id; //Chunk identifier
    unsigned int l_chunk_lenght; //Chunk lenght

    unsigned char l_char; //Char variable
    unsigned short l_qty; //Number of elements in each chunk

    unsigned short l_face_flags; //Flag that stores some face information

    if ((l_file=fopen ((MeshDirectory + fileName).c_str(), "rb"))== NULL)
	{
		std::cerr << "Failed to open 3ds mesh file: '" << (MeshDirectory + fileName) << "'." << std::endl;
		return 0; //Open the file
	}

    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    std::map<std::string, SVector3f> Materials;
    std::map<CMesh::SMeshBuffer *, std::string> FaceMaterials;
    std::string currentMat;

    int bufferCount = 0;

    while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file
    //while(!EOF)
    {
        //getch(); //Insert this command for debug (to wait for keypress for each chuck reading)

        fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
        //printf("ChunkID: %x\n",l_chunk_id); 
        fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
        //printf("ChunkLenght: %x\n",l_chunk_lenght);

        switch (l_chunk_id)
        {
            //----------------- MAIN3DS -----------------
            // Description: Main chunk, contains all the other chunks
            // Chunk ID: 4d4d 
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
            case 0x4d4d:
            break;

            //----------------- EDIT3DS -----------------
            // Description: 3D Editor chunk, objects layout info 
            // Chunk ID: 3d3d (hex)
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
            case 0x3d3d:
            break;

            //--------------- EDIT_OBJECT ---------------
            // Description: Object block, info for each object
            // Chunk ID: 4000 (hex)
            // Chunk Lenght: len(object name) + sub chunks
            //-------------------------------------------
            case 0x4000: 
                i=0;
                do
                {
                    fread (&l_char, 1, 1, l_file);
                    //p_object->name[i]=l_char; // Throw out name - why do we care? we don't! bwahahahaha
                    i++;
                } while(l_char != '\0' && i < 20);
                break;

            //--------------- OBJ_TRIMESH ---------------
            // Description: Triangular mesh, contains chunks for 3d mesh info
            // Chunk ID: 4100 (hex)
            // Chunk Lenght: 0 + sub chunks
            //-------------------------------------------
            case 0x4100:
                break;

            //--------------- TRI_VERTEXL ---------------
            // Description: Vertices list
            // Chunk ID: 4110 (hex)
            // Chunk Lenght: 1 x unsigned short (number of vertices) 
            //             + 3 x float (vertex coordinates) x (number of vertices)
            //             + sub chunks
            //-------------------------------------------
            case 0x4110: 
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                if (bufferCount)
                {
                    MeshWrapper->MeshBuffers.push_back(Mesh);
                    Mesh = new CMesh::SMeshBuffer();
                }
                Mesh->Vertices.resize(l_qty);
                bufferCount++;
                //printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
                    fread (& Mesh->Vertices[i].Position.X, sizeof(float), 1, l_file);
                    //printf("Vertices list x: %f\n",Mesh->Vertices[i].Position.X);
                    fread (& Mesh->Vertices[i].Position.Z, sizeof(float), 1, l_file);
                    //printf("Vertices list y: %f\n",Mesh->Vertices[i].Position.Y);
                    fread (& Mesh->Vertices[i].Position.Y, sizeof(float), 1, l_file);
                    //printf("Vertices list z: %f\n",Mesh->Vertices[i].Position.Z);
                }
                break;

            //--------------- TRI_FACEL1 ----------------
            // Description: Polygons (faces) list
            // Chunk ID: 4120 (hex)
            // Chunk Lenght: 1 x unsigned short (number of polygons) 
            //             + 3 x unsigned short (polygon points) x (number of polygons)
            //             + sub chunks
            //-------------------------------------------
            case 0x4120:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                Mesh->Triangles.resize(l_qty);
                //printf("Number of polygons: %d\n",l_qty); 
                for (i=0; i<l_qty; i++)
                {
                    Mesh->Triangles[i].Indices[0] = 0;
                    Mesh->Triangles[i].Indices[1] = 0;
                    Mesh->Triangles[i].Indices[2] = 0;
                    fread (& Mesh->Triangles[i].Indices[0], sizeof (unsigned short), 1, l_file);
                    //printf("Polygon point a: %d\n", Mesh->Triangles[i].Indices[0]);
                    fread (& Mesh->Triangles[i].Indices[1], sizeof (unsigned short), 1, l_file);
                    //printf("Polygon point b: %d\n", Mesh->Triangles[i].Indices[1]);
                    fread (& Mesh->Triangles[i].Indices[2], sizeof (unsigned short), 1, l_file);
                    //printf("Polygon point c: %d\n", Mesh->Triangles[i].Indices[2]);
                    fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
                    //printf("Face flags: %x\n",l_face_flags);
                }
                break;

            //------------- TRI_MAPPINGCOORS ------------
            // Description: Vertices list
            // Chunk ID: 4140 (hex)
            // Chunk Lenght: 1 x unsigned short (number of mapping points) 
            //             + 2 x float (mapping coordinates) x (number of mapping points)
            //             + sub chunks
            //-------------------------------------------
            case 0x4140:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                for (i=0; i<l_qty; i++)
                {
                    fread (& Mesh->Vertices[i].TextureCoordinates[0], sizeof (float), 1, l_file);
                    //printf("Mapping list u: %f\n", Mesh->Vertices[i].TextureCoordinates[0]);
                    fread (& Mesh->Vertices[i].TextureCoordinates[1], sizeof (float), 1, l_file);
                    //printf("Mapping list v: %f\n", Mesh->Vertices[i].TextureCoordinates[1]);
                }
                break;

            case 0xAFFF:
                {
                    //printf("found material block in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    //fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
                    break;
                }

            case 0x4130:
                {
                    //printf("found faces material block in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    i=0;
                    char name[20];
                    do
                    {
                        fread (&l_char, 1, 1, l_file);
                        name[i]=l_char;
                        i++;
                    } while(l_char != '\0' && i < 20);
                    FaceMaterials[Mesh] = name;
                    fseek(l_file, l_chunk_lenght - i - 6, SEEK_CUR);
                    break;
                }

            case 0xA000:
                {
                    //printf("found material name in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    i=0;
                    char name[20];
                    do
                    {
                        fread (&l_char, 1, 1, l_file);
                        name[i]=l_char;
                        i++;
                    } while(l_char != '\0' && i < 20);
                    currentMat = name;
                    fseek(l_file, l_chunk_lenght - i - 6, SEEK_CUR);
                    break;
                }

            case 0xA010:
                {
                    //printf("found ambient block in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
                    break;
                }

            case 0xA020:
                {
                    //printf("found diffuse block in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    unsigned char what[1000];
                    fread(what, 1, l_chunk_lenght-6, l_file);
                    if (l_chunk_lenght == 15)
                    {
                        Materials[currentMat].X = what[6] / 256.f;
                        Materials[currentMat].Y = what[7] / 256.f;
                        Materials[currentMat].Z = what[8] / 256.f;
                    }
                    else if (l_chunk_lenght == 24)
                    {
                        Materials[currentMat].X = (*(float *)& what[6]);// (float) (std::numeric_limits<unsigned short>::max());
                        Materials[currentMat].Y = (*(float *)& what[10]);// (float) (std::numeric_limits<unsigned short>::max());
                        Materials[currentMat].Z = (*(float *)& what[14]);// (float) (std::numeric_limits<unsigned short>::max());
                    }
                    //fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
                    break;
                }

            case 0xA030:
                {
                    //printf("found diffuse block in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
                    break;
                }

            case 0xA040:
                {
                    //printf("found specular block in %s (%d)!\n", fileName.c_str(), l_chunk_lenght);
                    fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
                    break;
                }

            //----------- Skip unknow chunks ------------
            //We need to skip all the chunks that currently we don't use
            //We use the chunk lenght information to set the file pointer
            //to the same level next chunk
            //-------------------------------------------
            default:
                    fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        } 
    }
    fclose (l_file);

    for (std::map<CMesh::SMeshBuffer *, std::string>::iterator it = FaceMaterials.begin(); it != FaceMaterials.end(); ++ it)
        it->first->Material.DiffuseColor = Materials[it->second];

    MeshWrapper->MeshBuffers.push_back(Mesh);

	if (useCache)
		LoadedMeshes[fileName] = MeshWrapper;
    return MeshWrapper;
}

CMesh * const CMeshLoader::loadAsciiMesh(std::string const & fileName)
{
    std::map<std::string, CMesh *>::iterator it = LoadedMeshes.find(fileName);

    if (it != LoadedMeshes.end())
    {
        return it->second;
    }

    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    std::ifstream File;
    File.open((MeshDirectory + fileName).c_str());

    if (! File.is_open())
    {
        std::cerr << "Unable to open ascii mesh file: " << fileName << std::endl;
        return 0;
    }

    while (File)
    {
        std::string ReadString;
        std::getline(File, ReadString);

        std::stringstream Stream(ReadString);

        std::string Label;
        Stream >> Label;

        if (Label.find("#") != std::string::npos)
        {
            // Comment, skip
            continue;
        }

        if ("Vertex" == Label)
        {
            int Index;
            Stream >> Index; // We don't care, throw it away

            SVector3f Position;
            Stream >> Position.X;
            Stream >> Position.Y;
            Stream >> Position.Z;

            SVertex Vertex;
            Vertex.Position = Position;

            Mesh->Vertices.push_back(Vertex);
        }
        else if ("Face" == Label)
        {
            int Index;
            Stream >> Index; // We don't care, throw it away

            int Vertex1, Vertex2, Vertex3;
            Stream >> Vertex1;
            Stream >> Vertex2;
            Stream >> Vertex3;

            CMesh::STriangle Triangle;
            Triangle.Indices[0] = Vertex1 - 1;
            Triangle.Indices[1] = Vertex2 - 1;
            Triangle.Indices[2] = Vertex3 - 1;

            size_t Location;
            if ((Location = ReadString.find("{")) != std::string::npos) // there is a color
            {
                Location = ReadString.find("rgb=(");
                Location += 5; // rgb=( is 5 characters

                ReadString = ReadString.substr(Location);
                std::stringstream Stream(ReadString);
                float Color;
                Stream >> Color;
                //Triangle.Color.Red = Color;
                Stream >> Color;
                //Triangle.Color.Green = Color;
                Stream >> Color;
                //Triangle.Color.Blue = Color;
            }

            Mesh->Triangles.push_back(Triangle);
        }
        else if ("" == Label)
        {
            // Just a new line, carry on...
        }
        else if ("Corner" == Label)
        {
            // We're not doing any normal calculations... (oops!)
        }
        else
        {
            std::cerr << "While parsing ASCII mesh: Expected 'Vertex' or 'Face' label, found '" << Label << "'." << std::endl;
        }
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    LoadedMeshes[fileName] = MeshWrapper;
    return MeshWrapper;
}

CMesh * const CMeshLoader::loadObjMesh(std::string const & fileName)
{
    std::map<std::string, CMesh *>::iterator it = LoadedMeshes.find(fileName);

    if (it != LoadedMeshes.end())
    {
        return it->second;
    }

    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    std::ifstream File;
    File.open((MeshDirectory + fileName).c_str());

    if (! File.is_open())
    {
        std::cerr << "Unable to open obj mesh file: " << fileName << std::endl;
        return 0;
    }

    while (File)
    {
        std::string ReadString;
        std::getline(File, ReadString);

		std::replace(ReadString.begin(), ReadString.end(), '/', ' ');
        std::stringstream Stream(ReadString);

        std::string Label;
        Stream >> Label;

        if ("v" == Label)
        {
            SVector3f Position;
            Stream >> Position.X;
            Stream >> Position.Y;
            Stream >> Position.Z;

            SVertex Vertex;
            Vertex.Position = Position;

            Mesh->Vertices.push_back(Vertex);
        }
		else if ("vn" == Label)
        {
            SVector3f Normal;
            Stream >> Normal.X;
            Stream >> Normal.Y;
            Stream >> Normal.Z;

			SVertex & Vertex = Mesh->Vertices.back();
			Vertex.Normal = Normal;
        }
		else if ("vt" == Label)
        {
            SVector2f TexCoords;
            Stream >> TexCoords.X;
            Stream >> TexCoords.Y;

			SVertex & Vertex = Mesh->Vertices.back();
			Vertex.TextureCoordinates = TexCoords;
        }
		else if ("#_#tangent" == Label)
        {
            SVector3f Tangent;
            Stream >> Tangent.X;
            Stream >> Tangent.Y;
            Stream >> Tangent.Z;

			SVertex & Vertex = Mesh->Vertices.back();
			//Vertex.Tangent = Tangent;
        }
		else if ("#_#binormal" == Label)
        {
            SVector3f Binormal;
            Stream >> Binormal.X;
            Stream >> Binormal.Y;
            Stream >> Binormal.Z;

			SVertex & Vertex = Mesh->Vertices.back();
			//Vertex.Binormal = Binormal;
        }
        else if ("f" == Label)
        {
            int Vertex1, Vertex2, Vertex3;
            Stream >> Vertex1;
            Stream >> Vertex2;
            Stream >> Vertex3;

            CMesh::STriangle Triangle;
            Triangle.Indices[0] = Vertex1 - 1;
            Triangle.Indices[1] = Vertex2 - 1;
            Triangle.Indices[2] = Vertex3 - 1;

            Mesh->Triangles.push_back(Triangle);
        }
		else if ("#faces" == Label)
        {
            // Number of faces, not particularily useful to us...
        }
        else if ("" == Label)
        {
            // Just a new line, carry on...
        }
        else
        {
            std::cerr << "While parsing OBJ mesh: Unexpected label '" << Label << "'." << std::endl;
        }
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    LoadedMeshes[fileName] = MeshWrapper;
    return MeshWrapper;
}

CMesh * const CMeshLoader::createCubeMesh()
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(24);
    Mesh->Vertices[0].Position = SVector3f(-0.5, -0.5, -0.5);
    Mesh->Vertices[1].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[2].Position = SVector3f( 0.5,  0.5, -0.5);
    Mesh->Vertices[3].Position = SVector3f( 0.5, -0.5, -0.5);

    Mesh->Vertices[4].Position = SVector3f( 0.5, -0.5, -0.5);
    Mesh->Vertices[5].Position = SVector3f( 0.5, 0.5, -0.5);
    Mesh->Vertices[6].Position = SVector3f( 0.5, 0.5,  0.5);
    Mesh->Vertices[7].Position = SVector3f( 0.5, -0.5,  0.5);

    Mesh->Vertices[8].Position = SVector3f( 0.5, -0.5,  0.5);
    Mesh->Vertices[9].Position = SVector3f( 0.5,  0.5,  0.5);
    Mesh->Vertices[10].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[11].Position = SVector3f(-0.5, -0.5,  0.5);

    Mesh->Vertices[12].Position = SVector3f(-0.5, -0.5,  0.5);
    Mesh->Vertices[13].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[14].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[15].Position = SVector3f(-0.5, -0.5, -0.5);

    Mesh->Vertices[16].Position = SVector3f(-0.5,  0.5, -0.5);
    Mesh->Vertices[17].Position = SVector3f(-0.5,  0.5,  0.5);
    Mesh->Vertices[18].Position = SVector3f( 0.5,  0.5,  0.5);
    Mesh->Vertices[19].Position = SVector3f( 0.5,  0.5, -0.5);

    Mesh->Vertices[20].Position = SVector3f( 0.5, -0.5, -0.5);
    Mesh->Vertices[21].Position = SVector3f( 0.5, -0.5,  0.5);
    Mesh->Vertices[22].Position = SVector3f(-0.5, -0.5,  0.5);
    Mesh->Vertices[23].Position = SVector3f(-0.5, -0.5, -0.5);

    Mesh->Triangles.resize(12);
    for (int i = 0; i < 6; ++ i)
    {
        Mesh->Vertices[4*i + 0].TextureCoordinates = SVector2f(0, 1);
        Mesh->Vertices[4*i + 1].TextureCoordinates = SVector2f(0, 0);
        Mesh->Vertices[4*i + 2].TextureCoordinates = SVector2f(1, 0);
        Mesh->Vertices[4*i + 3].TextureCoordinates = SVector2f(1, 1);

        Mesh->Triangles[2*i].Indices[0] = 4*i + 0;
        Mesh->Triangles[2*i].Indices[1] = 4*i + 1;
        Mesh->Triangles[2*i].Indices[2] = 4*i + 2;

        Mesh->Triangles[2*i+1].Indices[0] = 4*i + 0;
        Mesh->Triangles[2*i+1].Indices[1] = 4*i + 2;
        Mesh->Triangles[2*i+1].Indices[2] = 4*i + 3;
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}

CMesh * const CMeshLoader::createDiscMesh(unsigned int const Triangles)
{
    CMesh * MeshWrapper = new CMesh();
    CMesh::SMeshBuffer * Mesh = new CMesh::SMeshBuffer();

    Mesh->Vertices.resize(Triangles * 3);
    Mesh->Triangles.resize(Triangles);

    for (unsigned int i = 0; i < Triangles; ++ i)
    {
        Mesh->Vertices[i*3 + 0].Position.X = 0;
        Mesh->Vertices[i*3 + 0].Position.Y = 0;
        Mesh->Vertices[i*3 + 0].Position.Z = 0;

        Mesh->Vertices[i*3 + 1].Position.X = 0.5f * sin(float(i) / float(Triangles) * 2.f * 3.14159f);
        Mesh->Vertices[i*3 + 1].Position.Y = 0;
        Mesh->Vertices[i*3 + 1].Position.Z = 0.5f * cos(float(i) / float(Triangles) * 2.f * 3.14159f);

        Mesh->Vertices[i*3 + 2].Position.X = 0.5f * sin(float(i+1) / float(Triangles) * 2.f * 3.14159f);
        Mesh->Vertices[i*3 + 2].Position.Y = 0;
        Mesh->Vertices[i*3 + 2].Position.Z = 0.5f * cos(float(i+1) / float(Triangles) * 2.f * 3.14159f);

		Mesh->Vertices[i*3 + 0].Normal = SVector3f(0, 0, 1);
		Mesh->Vertices[i*3 + 1].Normal = SVector3f(0, 0, 1);
		Mesh->Vertices[i*3 + 2].Normal = SVector3f(0, 0, 1);

        Mesh->Triangles[i].Indices[0] = i*3 + 0;
        Mesh->Triangles[i].Indices[1] = i*3 + 1;
        Mesh->Triangles[i].Indices[2] = i*3 + 2;
    }

    for (unsigned int i = 0; i < Mesh->Vertices.size(); ++ i)
    {
        Mesh->Vertices[i].TextureCoordinates = SVector2f(Mesh->Vertices[i].Position.X, Mesh->Vertices[i].Position.Y) + SVector2f(0.5f);
    }

    MeshWrapper->MeshBuffers.push_back(Mesh);

    MeshWrapper->calculateNormalsPerFace();
    return MeshWrapper;
}
