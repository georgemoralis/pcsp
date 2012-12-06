#ifndef gl_OcclusionQuery_h__
#define gl_OcclusionQuery_h__

#include "opengl/gl_Core.h"

class gl_OcclusionQuery
:   public gl_Core
{
public:
    gl_OcclusionQuery()
    :   m_oq(-1)
    {
        GenQueries(1, (GLuint *)&m_oq);
    }

    ~gl_OcclusionQuery()
    {
        DeleteQueries(1, (GLuint *)&m_oq);
    }

    __forceinline void BeginBBOX()
    {
        PushAttrib(ENABLE_BIT|COLOR_BUFFER_BIT|STENCIL_BUFFER_BIT|DEPTH_BUFFER_BIT);

        ColorMask(false, false, false, false);
        DepthMask(false);

        Disable(BLEND);
        Disable(STENCIL_TEST);
        Disable(LIGHTING);
        Disable(TEXTURE_2D);
        Disable(ALPHA_TEST);
        Disable(FOG);
        Disable(DEPTH_TEST);
        Disable(LOGIC_OP);
        Disable(CULL_FACE);
        Disable(SCISSOR_TEST);

        BeginQuery(SAMPLES_PASSED, m_oq);

        Begin(QUADS);
    }

    __forceinline void AddBBOX(f32 bbox[8][3])
    {
        // Front face
        glVertex3fv(bbox[0]);
        glVertex3fv(bbox[1]);
        glVertex3fv(bbox[3]);
        glVertex3fv(bbox[2]);

        // Back face
        glVertex3fv(bbox[4]);
        glVertex3fv(bbox[5]);
        glVertex3fv(bbox[7]);
        glVertex3fv(bbox[6]);

        // Right face
        glVertex3fv(bbox[1]);
        glVertex3fv(bbox[5]);
        glVertex3fv(bbox[7]);
        glVertex3fv(bbox[3]);

        // Left face
        glVertex3fv(bbox[0]);
        glVertex3fv(bbox[4]);
        glVertex3fv(bbox[6]);
        glVertex3fv(bbox[2]);

        // Top face
        glVertex3fv(bbox[2]);
        glVertex3fv(bbox[3]);
        glVertex3fv(bbox[7]);
        glVertex3fv(bbox[6]);

        // Bottom face
        glVertex3fv(bbox[0]);
        glVertex3fv(bbox[1]);
        glVertex3fv(bbox[5]);
        glVertex3fv(bbox[4]);
    }

    __forceinline void EndBBOX()
    {
        End();

        EndQuery(SAMPLES_PASSED);

        Flush();
        PopAttrib();
    }

    __forceinline bool IsOccluded()
    {
        int result = 0;
        GetQueryObjectiv(m_oq, QUERY_RESULT, &result);
        return (0 == result);
    }

private:
#if 0
    static void MatrixConcatenate(f32 *result, f32 *ma, f32 *mb)
    {
        int i;
        f32 mb00, mb01, mb02, mb03,
            mb10, mb11, mb12, mb13,
            mb20, mb21, mb22, mb23,
            mb30, mb31, mb32, mb33;
        f32 mai0, mai1, mai2, mai3;

        mb00 = mb[ 0];  mb01 = mb[ 1];
        mb02 = mb[ 2];  mb03 = mb[ 3];
        mb10 = mb[ 4];  mb11 = mb[ 5];
        mb12 = mb[ 6];  mb13 = mb[ 7];
        mb20 = mb[ 8];  mb21 = mb[ 9];
        mb22 = mb[10];  mb23 = mb[11];
        mb30 = mb[12];  mb31 = mb[13];
        mb32 = mb[14];  mb33 = mb[15];

        for (i = 0; i < 4; i++)
        {
            mai0 = ma[i*4+0];  mai1 = ma[i*4+1];
            mai2 = ma[i*4+2];  mai3 = ma[i*4+3];

            result[i*4+0] = mai0 * mb00 + mai1 * mb10 + mai2 * mb20 + mai3 * mb30;
            result[i*4+1] = mai0 * mb01 + mai1 * mb11 + mai2 * mb21 + mai3 * mb31;
            result[i*4+2] = mai0 * mb02 + mai1 * mb12 + mai2 * mb22 + mai3 * mb32;
            result[i*4+3] = mai0 * mb03 + mai1 * mb13 + mai2 * mb23 + mai3 * mb33;
        }
    }

    __forceinline f32 DistanceFromPlane(f32 peq[4] , f32 p[3])
    {
        return ((peq)[0]*(p)[0] + (peq)[1]*(p)[1] + (peq)[2]*(p)[2] + (peq)[3]); 
    }
    
    void CalcViewVolumePlanes()
    {
/* Calculates the six view volume planes in object coordinate (OC) space.
       
       Algorithm:
       
       A view volume plane in OC is transformed into CC by multiplying it by
       the inverse of the combined ModelView and Projection matrix (M).
       Algebraically, this is written:
              -1
         P   M   = P
          oc        cc
       
       The resulting six view volume planes in CC are:
         [ -1  0  0  1 ]
         [  1  0  0  1 ]
         [  0 -1  0  1 ]
         [  0  1  0  1 ]
         [  0  0 -1  1 ]
         [  0  0  1  1 ]
       
       To transform the CC view volume planes into OC, we simply multiply
       the CC plane equations by the combined ModelView and Projection matrices
       using standard vector-matrix multiplication. Algebraically, this is written:  
         P   M = P
          cc      oc
       
       Since all of the CC plane equation components are 0, 1, or -1, full vector-
       matrix multiplication is overkill. For example, the first element of the
       first OC plane equation is computed as:
         A = -1 * m0 + 0 * m1 + 0 * m2 + 1 * m3
       This simplifies to:
         A = m3 - m0
       
       Other terms simplify similarly. In fact, all six plane equations can be
       computed as follows:
         [ m3-m0  m7-m4  m11-m8  m15-m12 ]
         [ m3+m0  m7+m4  m11+m8  m15+m12 ]
         [ m3-m1  m7-m5  m11-m9  m15-m13 ]
         [ m3+m1  m7+m5  m11+m9  m15+m13 ]
         [ m3-m2  m7-m6  m11-m10 m15-m14 ]
         [ m3+m2  m7+m6  m11+m10 m15+m14 ]
*/
        GLfloat ocEcMat[16], ecCcMat[16], ocCcMat[16];

        /* Get the modelview and projection matrices */
        GetFloatv(MODELVIEW_MATRIX,  ocEcMat);
        GetFloatv(PROJECTION_MATRIX, ecCcMat);

        /* ocCcMat transforms from OC (object coordinates) to CC (clip coordinates) */
        MatrixConcatenate(ocCcMat, ocEcMat, ecCcMat);

        /* Calculate the six OC plane equations. */
        m_plane_eqs[0][0] = ocCcMat[ 3] - ocCcMat[ 0]; 
        m_plane_eqs[0][1] = ocCcMat[ 7] - ocCcMat[ 4]; 
        m_plane_eqs[0][2] = ocCcMat[11] - ocCcMat[ 8]; 
        m_plane_eqs[0][3] = ocCcMat[15] - ocCcMat[12]; 

        m_plane_eqs[1][0] = ocCcMat[ 3] + ocCcMat[ 0]; 
        m_plane_eqs[1][1] = ocCcMat[ 7] + ocCcMat[ 4]; 
        m_plane_eqs[1][2] = ocCcMat[11] + ocCcMat[ 8]; 
        m_plane_eqs[1][3] = ocCcMat[15] + ocCcMat[12]; 

        m_plane_eqs[2][0] = ocCcMat[ 3] + ocCcMat[ 1]; 
        m_plane_eqs[2][1] = ocCcMat[ 7] + ocCcMat[ 5]; 
        m_plane_eqs[2][2] = ocCcMat[11] + ocCcMat[ 9]; 
        m_plane_eqs[2][3] = ocCcMat[15] + ocCcMat[13]; 

        m_plane_eqs[3][0] = ocCcMat[ 3] - ocCcMat[ 1]; 
        m_plane_eqs[3][1] = ocCcMat[ 7] - ocCcMat[ 5]; 
        m_plane_eqs[3][2] = ocCcMat[11] - ocCcMat[ 9]; 
        m_plane_eqs[3][3] = ocCcMat[15] - ocCcMat[13]; 

        m_plane_eqs[4][0] = ocCcMat[ 3] + ocCcMat[ 2]; 
        m_plane_eqs[4][1] = ocCcMat[ 7] + ocCcMat[ 6]; 
        m_plane_eqs[4][2] = ocCcMat[11] + ocCcMat[10]; 
        m_plane_eqs[4][3] = ocCcMat[15] + ocCcMat[14]; 

        m_plane_eqs[5][0] = ocCcMat[ 3] - ocCcMat[ 2]; 
        m_plane_eqs[5][1] = ocCcMat[ 7] - ocCcMat[ 6]; 
        m_plane_eqs[5][2] = ocCcMat[11] - ocCcMat[10]; 
        m_plane_eqs[5][3] = ocCcMat[15] - ocCcMat[14]; 
    }

    bool Culled(f32 bbox[8][3])
    {
        int i, j;
        int out, in;

        for (i = 0; i < 6; i++)
        {
            in  = 0;
            out = 0;
            for (j = 0; j < 8; j++)
            {
                if (DistanceFromPlane(m_plane_eqs[i], bbox[j]) < 0.0f)
                {
                    out++;
                    if (in) break;
                }
                else
                {
                    in++;
                    if (out) break;
                }
            }
            if (!in)
            {
                // all of the eight vertices are trivially culled
                return true;
            }
        }
    
        return false;
    }
#endif
    GLuint m_oq;
#if 0
    f32    m_plane_eqs[6][4]; // Storage for the six planes, left right top bottom near far
    bool   m_culled;
#endif
};

#endif // gl_OcclusionQuery_h__