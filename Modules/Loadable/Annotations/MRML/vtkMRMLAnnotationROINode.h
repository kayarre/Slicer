#ifndef __vtkMRMLAnnotationROINode_h
#define __vtkMRMLAnnotationROINode_h

#include "vtkSlicerAnnotationsModuleMRMLExport.h"
#include "vtkMRMLAnnotationLinesNode.h"

class vtkMatrix4x4;
class vtkPlanes;
class vtkAbstractTransform;
class vtkMRMLScene;

/// \ingroup Slicer_QtModules_Annotation
class  VTK_SLICER_ANNOTATIONS_MODULE_MRML_EXPORT vtkMRMLAnnotationROINode
  : public vtkMRMLAnnotationLinesNode
{
public:
  static vtkMRMLAnnotationROINode *New();
  vtkTypeMacro(vtkMRMLAnnotationROINode,vtkMRMLAnnotationLinesNode);
  /// Description:
  /// Just prints short summary
  void PrintAnnotationInfo(ostream& os, vtkIndent indent, int titleFlag = 1) VTK_OVERRIDE;

  //--------------------------------------------------------------------------
  // MRMLNode methods
  //--------------------------------------------------------------------------

  virtual vtkMRMLNode* CreateNodeInstance() VTK_OVERRIDE;
  /// Description:
  /// Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() VTK_OVERRIDE {return "AnnotationROI";}

  virtual const char* GetIcon() VTK_OVERRIDE {return ":/Icons/AnnotationROI.png";}

  // Description:
  /// Read node attributes from XML file
  virtual void ReadXMLAttributes( const char** atts) VTK_OVERRIDE;

  /// Description:
  /// Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent) VTK_OVERRIDE;


  /// Description:
  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node) VTK_OVERRIDE;

  void UpdateScene(vtkMRMLScene *scene) VTK_OVERRIDE;

  /// Description:
  /// alternative method to propagate events generated in Display nodes
  virtual void ProcessMRMLEvents ( vtkObject * /*caller*/,
                                   unsigned long /*event*/,
                                   void * /*callData*/ ) VTK_OVERRIDE;

  ///
  /// Indicates if the ROI is updated interactively
  vtkBooleanMacro(InteractiveMode, int);
  vtkGetMacro(InteractiveMode, int);
  vtkSetMacro(InteractiveMode, int);


  ///
  /// Indicates if the ROI box is inside out
  vtkBooleanMacro(InsideOut, int);
  vtkGetMacro(InsideOut, int);
  vtkSetMacro(InsideOut, int);

  /// Description:
  /// KP Define - should be part of AnnotationRulerDisplayNode
  double GetROIAnnotationScale();
  void SetROIAnnotationScale(double init);

  /// Description:
  /// get/set the visibility of any text associated with the ROI
  int GetROIAnnotationVisibility();
  void SetROIAnnotationVisibility(int flag);

//  int SetROI(vtkIdType line1Id, int sel, int vis);

  /// Description:
  /// get/set the point representation color
  double *GetPointColor();
  void SetPointColor( double initColor[3]);

  /// Description:
  /// get/set the line representation color
  double *GetLineColor();
  void SetLineColor(double newColor[3]);

  /// Description:
  /// get/set the ROI annotation text color
  double *GetROIAnnotationTextColor();
  void SetROIAnnotationTextColor(double initColor[3]);

  /// Description:
  /// transform utility functions
  virtual void ApplyTransformMatrix(vtkMatrix4x4* transformMatrix) VTK_OVERRIDE;
  virtual void ApplyTransform(vtkAbstractTransform* transform) VTK_OVERRIDE;
  virtual void GetTransformedPlanes(vtkPlanes *planes);

  /// Description:
  /// Add ROI to scene and add display nodes
  void Initialize(vtkMRMLScene* mrmlScene) VTK_OVERRIDE;

  ///
  /// Get/Set for ROI Position in RAS cooridnates
  /// Note: The ROI Position is the center of the ROI
  /// Old API:
  /// void SetXYZ(double X, double Y, double Z);
  /// void SetXYZ(double* XYZ);
  /// vtkGetVectorMacro(XYZ,double,3);
  //double* GetXYZ() {return this->GetControlPointCoordinates(0);}
  /// returns true and control point coordinate 0 on success, false and 0,0,0 on failure
  bool GetXYZ(double point[3]);
  int SetXYZ(double newControl[3])
  {
    return this->SetControlPoint(0, newControl);
  }

  int SetXYZ(double nC1, double nC2, double nC3)
  {
    double newControl[3] = {nC1,nC2,nC3};
    return this->SetXYZ(newControl) ;
  }

  /// Get/Set for radius of the ROI in RAS cooridnates
  /// Old API:
  /// void SetRadiusXYZ(double RadiusX, double RadiusY, double RadiusZ);
  /// void SetRadiusXYZ(double* RadiusXYZ);
  /// vtkGetVectorMacro(RadiusXYZ,double,3);
  bool GetRadiusXYZ(double point[3]);

  int SetRadiusXYZ(double newControl[3])
  {
    return this->SetControlPoint(1, newControl);
  }

  int SetRadiusXYZ(double nC1, double nC2, double nC3)
  {
    double newControl[3] = {nC1,nC2,nC3};
    return this->SetRadiusXYZ(newControl);
  }


  /// Get/Set for LabelText
  vtkSetStringMacro(LabelText);
  vtkGetStringMacro(LabelText);

  /// Get/Set for the volume node ID associated with this ROI
  vtkGetStringMacro(VolumeNodeID);
  vtkSetStringMacro(VolumeNodeID);

  /// Get bounding box in global RAS form (xmin,xmax, ymin,ymax, zmin,zmax).
  /// The default implementation in the model node would not work correctly, as the polydata
  /// in this class is used for storing the centerpoint position and radius.
  /// \sa GetBounds()
  virtual void GetRASBounds(double bounds[6]) VTK_OVERRIDE;

  /// Get bounding box in global RAS form (xmin,xmax, ymin,ymax, zmin,zmax).
  /// This method always returns the bounds of the untransformed object.
  /// \sa GetRASBounds()
  virtual void GetBounds(double bounds[6]) VTK_OVERRIDE;

  enum
  {
      ROINodeAddedEvent = 0,
      ValueModifiedEvent,
  };


protected:
  vtkMRMLAnnotationROINode();
  ~vtkMRMLAnnotationROINode();
  vtkMRMLAnnotationROINode(const vtkMRMLAnnotationROINode&);
  void operator=(const vtkMRMLAnnotationROINode&);

  int InteractiveMode;

  int SetControlPoint(int id, double newControl[3]);

  int AddControlPoint(double newControl[3],int selectedFlag, int visibleFlag);

  /// Control the orientation of the normals
  int InsideOut;

  /// LabelText, here for backwards compatibility
  /// No effect on displayableManager side
  char *LabelText;

  /// The ID of the volume associated with the ROI
  char *VolumeNodeID;

};

#endif
