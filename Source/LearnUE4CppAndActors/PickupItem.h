#pragma once

#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class LEARNUE4CPPANDACTORS_API APickupItem : public AActor
{
	GENERATED_BODY()
    
public:	
	// Sets default values for this actor's properties
	APickupItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item)
    FString Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item)
    int32 Quantity;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item)
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Collision)
    USphereComponent* ProxSphere;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Item)
    UTexture2D* Icon;
    
    UFUNCTION(BlueprintNativeEvent, Category=Collision)
    void Prox(class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
